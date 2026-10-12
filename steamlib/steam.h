#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

uint32_t read_le32(const std::vector<uint8_t>& buf, size_t offset);

std::vector<uint8_t> zlib_decompress(const std::vector<uint8_t>& compressed);
std::vector<uint8_t> zlib_compress(const std::vector<uint8_t>& input, int level);
void package_unpack(const std::string& infilename, const std::string& outpath);
void package_pack(const std::string& directory, const std::string& outfilename);


