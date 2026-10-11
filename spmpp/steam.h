#pragma once
#include <string>
#include <vector>
uint32_t read_le32(const std::vector<uint8_t>& buf, size_t offset);
void package_unpack(std::string& infilename, std::string& outpath);
std::vector<uint8_t> zlib_decompress(const std::vector<uint8_t>& compressed);