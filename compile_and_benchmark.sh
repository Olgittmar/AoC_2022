#!/usr/bin/bash
conan install conan/\
 --output-folder=./\
 --build=missing\
 -pr:h=conan/profile_rel_with_deb_info.txt\
 -pr:b=conan/profile_rel_with_deb_info.txt\
 || ( cd -; exit 1; )
cd build/RelWithDebInfo/generators/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=/conan_toolchain.cmake\
 -DCMAKE_BUILD_TYPE=RelWithDebInfo\
 -S../../..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
ninja run_benchmark || ( cd -; exit 1; )
cd -