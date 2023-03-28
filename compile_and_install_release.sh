#!/usr/bin/bash
conan install conan/\
 --output-folder=./\
 --build=missing\
 -pr:h=conan/profile_release.txt\
 -pr:b=conan/profile_release.txt\
 || ( cd -; exit 1; )
cd build/Release/generators/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake\
 -DCMAKE_BUILD_TYPE=Release\
 -S../../..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
cd -