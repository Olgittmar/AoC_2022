#!/usr/bin/bash
if [ ! -d build_release ] 
then
  mkdir build_release
fi
cd build_release/
conan install ../conan/\
 -if=../build_release/\
 --build=missing\
 -pr=../conan/profile_release.txt\
 -pr:b=../conan/profile_release.txt\
 || ( cd -; exit 1; )
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake\
 -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja\
 -DCMAKE_INSTALL_PREFIX=../install_release\
 -DCMAKE_C_COMPILER=/usr/bin/clang\
 -DCMAKE_CXX_COMPILER=/usr/bin/clang++\
 -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE\
 -DCMAKE_BUILD_TYPE=Release\
 -S..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
cd -