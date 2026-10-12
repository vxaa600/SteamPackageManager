# spmpp
a fast steam package manager written in C++ 
# features
- extract .pkg files
- pack .pkg files from directories
- zlib-ng compression
- x64 and x86 support
# install
download the latest [release](https://github.com/vxaa600/spmpp/releases), no install needed
# usage
extract a package \
`spmpp.exe -e -i input.pkg -o output_folder`

create a package\
`spmpp.exe -p -i input_folder -o output.pkg`

### arguments
`-e` - extract package \
`-p` - write package \
`-i` - input file or folder \
`-o` - output file or folder \
`-h` - usage 
# build
requirements:
- vs2026 with C++ support
- vcpkg
- C++23

dependencies are in `vcpkg.conf`

open SPM++.slnx in vs, select release x64/x86, then build
# license
see [LICENSE](https://github.com/vxaa600/spmpp/blob/main/LICENSE)
