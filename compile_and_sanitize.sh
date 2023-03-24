#!/usr/bin/bash
if [ ! -d build_sanitize ] 
then
  mkdir build_sanitize
fi
cd build_sanitize/

## Memory
conan install ../conan/\
 --output-folder=./mem_san/\
 --build=missing\
 -pr:h=../conan/profile_sanitize_memory.txt\
 -pr:b=../conan/profile_sanitize_memory.txt\
 || ( cd -; exit 1; )

cd mem_san/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake\
 -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja\
 -DCMAKE_INSTALL_PREFIX=./install\
 -DCMAKE_C_COMPILER=/usr/bin/clang\
 -DCMAKE_CXX_COMPILER=/usr/bin/clang++\
 -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE\
 -DCMAKE_BUILD_TYPE=Debug\
 -S../..\
 -B.\
 || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
ninja run_tests || ( cd -; exit 1; )
cd -

cd ..