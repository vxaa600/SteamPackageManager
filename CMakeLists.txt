cmake_minimum_required(VERSION 3.20)
project(SteamPackageManager LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZLIBNG REQUIRED IMPORTED_TARGET zlib-ng)

add_library(steamlib STATIC
    steamlib/steam.cpp
)

target_include_directories(steamlib PUBLIC
    steamlib
)

target_link_libraries(steamlib PUBLIC
    PkgConfig::ZLIBNG
)

add_executable(SteamPackageManager
    SteamPackageManager/main.cpp
)

target_link_libraries(SteamPackageManager PRIVATE steamlib)