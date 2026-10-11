#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <zlib.h>

namespace fs = std::filesystem;

/* read little endian */
uint32_t read_le32(const std::vector<uint8_t>& buf, size_t offset) {
    return static_cast<uint32_t>(buf[offset])
        | (static_cast<uint32_t>(buf[offset + 1]) << 8)
        | (static_cast<uint32_t>(buf[offset + 2]) << 16)
        | (static_cast<uint32_t>(buf[offset + 3]) << 24);
}

std::vector<uint8_t> zlib_decompress(const std::vector<uint8_t>& compressed)
{
    size_t buffer_size{ 0x8000 };
    std::vector<uint8_t> decompressed(buffer_size);

    while (true) {
        uLongf dest_len{ static_cast<uLongf>(buffer_size) };

        int result = uncompress(
            decompressed.data(), &dest_len,
            compressed.data(), static_cast<uLong>(compressed.size())
        );

        if (result == Z_OK) {
            decompressed.resize(dest_len);
            return decompressed;
        }
        else if (result == Z_BUF_ERROR) {
            buffer_size *= 2;
            decompressed.resize(buffer_size);
        }
        else {
            throw std::runtime_error("zlib decompression failed");
        }
    }
}

void package_unpack(const std::string& infilename, const std::string& outpath)
{
    if (!fs::exists(outpath)) {
        fs::create_directories(outpath);
    }

    std::ifstream infile(infilename, std::ios::binary);
    std::vector<uint8_t> package{ (std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>() }; // uint8_t vector equivalent to b""
    infile.close();

    std::vector<uint8_t> header{ package.end() - 9, package.end() };

    size_t header_start{ package.size() - 9 };
    uint32_t numfiles{ read_le32(package, header_start + 5) };

    size_t index{ package.size() - (9 + 16) };

    for (uint32_t i{}; i < numfiles; i++) {
        uint32_t packed_size{read_le32(package, index + 4)};
        uint32_t file_start{ read_le32(package, index + 8) };
        uint32_t filename_len{ read_le32(package, index + 12) };

        std::string filename(package.begin() + (index - filename_len), package.begin() + (index - 1)); // like filename = package[index - filename_len:index - 1]
        fs::path filepath(filename);
        std::string dir{ filepath.parent_path().string()};
        std::string basename{ filepath.filename().string() };
        
        index -= (filename_len + 16);

        std::vector<uint8_t> file{};

        while (packed_size > 0) {
            uint32_t compressed_len{ read_le32(package, (file_start) )};
            size_t compressed_start{ file_start + 4 };
            size_t compressed_end{ compressed_start + compressed_len };
            std::vector<uint8_t> compressed_data(package.begin() + compressed_start, package.begin() + compressed_end);
            std::vector<uint8_t> decompressed_data{ zlib_decompress(compressed_data) };
            file.insert(file.end(), decompressed_data.begin(), decompressed_data.end());
            file_start = static_cast<uint32_t>(compressed_end);;
            packed_size -= compressed_len;

        }
        fs::path outsubpath{ fs::path(outpath) / dir };
        if (!fs::exists(outsubpath)) {
            fs::create_directories(outsubpath);
        }
        fs::path outfullfilename{ fs::path(outpath) / filename };
        std::ofstream outfile(outfullfilename, std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(file.data()), file.size());
        outfile.close();
        std::cout << outfullfilename << " written\n";
    }   
}

void package_pack(const std::string& directory, const std::string& outfilename)
{

    std::vector<fs::path> filenames{};
    std::cout << directory << '\n';
    for (const auto& entry : fs::recursive_directory_iterator(directory))// : means in
    {
        if (entry.is_regular_file())
        {
            fs::path filename{ entry.path() };
            filenames.push_back(filename);
        }
    }
    for (const auto& filename : filenames) {
        std::cout << filename << '\n';
    }
    size_t outfileoffset{};
    std::vector<uint8_t> datasection; // uint8_t vector equivalent to b""
    std::vector<uint8_t> indexsection;
    uint32_t numberoffiles{};
    for (const auto& filename : filenames) {
        std::ifstream infile(filename, std::ios::binary);
        std::vector<uint8_t> filedata{ (std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>() };
        infile.close(); 

        size_t index{};
        size_t packedbytes{};
    }
}