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
### windows
**requirements:**
- vs2026 with C++ support
- vcpkg
- C++23

dependencies are in `vcpkg.conf`

open SPM++.slnx in vs, select release x64/x86, then build

### linux
> [!WARNING] \
> i havent tested this yet so please leave feedback

**requirements:**

- linux 
- cmakke 3.20+
- C++23 compiler
- pkg-config
- zlib-ng 

**step 1: dependencies** \
`sudo apt install build-essential cmake pkg-config` 

**step 2: clone repo** 

`git clone https://github.com/vxaa600/SteamPackageManager.git`
`cd SteamPackageManager`

**step 3: compile** \
`mkdir build`\
`cd build`\
`cmake .. -DCMAKE_BUILD_TYPE=Release`\
`make -j$(nproc)`

**step 4: run** \
`./SteamPackageManager -e -i input.pkg -o output_folder`\
`./SteamPackageManager -e -i input_folder -o output.pkg`
# license
see [LICENSE](https://github.com/vxaa600/SteamPackageManager/blob/main/LICENSE)
