#!/usr/bin/bash
if [ ! -d build ] 
then
  mkdir build
fi
conan install conan/\
 --output-folder=build/\
 --build=missing\
 -pr:h=conan/profile_debug.txt\
 -pr:b=conan/profile_debug.txt\
 || ( cd -; exit 1; )
cd build/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=/conan_toolchain.cmake\
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
cd -
# ./install/bin/AoC_2022_main
