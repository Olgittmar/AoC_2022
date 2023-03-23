#!/usr/bin/bash
if [ ! -d build_benchmark ] 
then
  mkdir build_benchmark
fi
conan install conan/\
 --output-folder=build_benchmark/\
 --build=missing\
 -pr:h=conan/profile_rel_with_deb_info.txt\
 -pr:b=conan/profile_rel_with_deb_info.txt\
 || ( cd -; exit 1; )
cd build_benchmark/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake\
 -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja\
 -DCMAKE_INSTALL_PREFIX=../install_benchmark\
 -DCMAKE_C_COMPILER=/usr/bin/clang\
 -DCMAKE_CXX_COMPILER=/usr/bin/clang++\
 -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE\
 -DCMAKE_BUILD_TYPE=RelWithDebInfo\
 -S..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
ninja run_benchmark || ( cd -; exit 1; )
cd -
# ./install/bin/AoC_2022_main
