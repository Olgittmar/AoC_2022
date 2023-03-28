#!/usr/bin/bash
conan install conan/\
 --output-folder=./out\
 --build=missing\
 -pr:h=conan/profile_debug.txt\
 -pr:b=conan/profile_debug.txt\
 || ( cd -; exit 1; )
cd out/build/Debug/generators/
cmake ..\
 -G Ninja\
 -DCMAKE_TOOLCHAIN_FILE=/conan_toolchain.cmake\
 -DCMAKE_BUILD_TYPE=Debug\
 -S../../../..\
 -B.\
 || ( cd -; exit 1; )
ninja format_project || ( cd -; exit 1; )
ninja install || ( cd -; exit 1; )
ninja run_tests || ( cd -; exit 1; )
ninja run_clang_tidy || ( cd -; exit 1; )
ninja run_cppcheck || ( cd -; exit 1; )
cd -