#!/usr/bin/bash
conan install conan/\
 --output-folder=./\
 --build=missing\
 -pr:h=conan/profile_debug.txt\
 -pr:b=conan/profile_debug.txt\
 || ( cd -; exit 1; )
cd build/Debug/generators/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=/conan_toolchain.cmake\
 -DCMAKE_BUILD_TYPE=Debug\
 -S../../..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
cd -