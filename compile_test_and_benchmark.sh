#!/usr/bin/bash
if [ ! -d build ] 
then
  mkdir build
fi
cd build/
conan install ../conan/\
 -if=../build/\
 --build=missing\
 -pr=../conan/profile.txt\
 -pr:b=../conan/profile.txt\
 || ( cd -; exit 1; )
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake\
 -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja\
 -DCMAKE_INSTALL_PREFIX=../install\
 -DCMAKE_C_COMPILER=/usr/bin/clang\
 -DCMAKE_CXX_COMPILER=/usr/bin/clang++\
 -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE\
 -DCMAKE_BUILD_TYPE=Debug\
 -S..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
ninja run_tests || ( cd -; exit 1; )
ninja run_benchmark || ( cd -; exit 1; )
cd -
# ./install/bin/AoC_2022_main
