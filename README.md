# Steam Package Manager
a fast steam package manager written in C++ 
# features
- extract .pkg files
- pack .pkg files from directories
- zlib-ng compression
- x64 and x86 support
# install
download the latest [release](https://github.com/vxaa600/SteamPackageManager/releases), no install needed
# usage
extract a package \
`SteamPackageManager -e -i input.pkg -o output_folder`

create a package\
`SteamPackageManager -p -i input_folder -o output.pkg`

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

**CMAKE WIP**
# license
see [LICENSE](https://github.com/vxaa600/SteamPackageManager/blob/main/LICENSE)
