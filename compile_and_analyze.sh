#!/usr/bin/bash
conan install conan/\
 --output-folder=./\
 --build=missing\
 -pr:h=conan/profile_debug.txt\
 -pr:b=conan/profile_debug.txt
cd build/Debug/generators/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=/conan_toolchain.cmake\
 -DCMAKE_BUILD_TYPE=Debug\
 -S../../..\
 -B.\
 &&
ninja format_project &&
ninja install &&
ninja run_tests &&
ninja run_clang_tidy &&
ninja run_cppcheck
cd -