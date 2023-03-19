set(BENCHMARK_PROJECT_NAME ${CMAKE_PROJECT_NAME}_BENCHMARK)
project(${BENCHMARK_PROJECT_NAME} CXX)

find_package(benchmark REQUIRED)

set(BENCHMARK_MAIN_SOURCE_FILES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/benchmark_Solutions.cpp>")
set(BENCHMARK_SOURCE_FILES ${BENCHMARK_MAIN_SOURCE_FILES})

# Solutions benchmark
add_executable(benchmark_Solutions ${BENCHMARK_MAIN_SOURCE_FILES})
target_compile_features(benchmark_Solutions PUBLIC cxx_std_20)

add_dependencies(benchmark_Solutions Solutions)
target_link_libraries(benchmark_Solutions
	benchmark::benchmark
	benchmark::benchmark_main
	Solutions
)

target_include_directories(benchmark_Solutions
	PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/Solutions>"
	"$<INSTALL_INTERFACE:lib/Solutions>"
)

# target_include_directories(benchmark_Solutions
# 	SYSTEM BEFORE
# 	PRIVATE ${GTest_INCLUDE_DIRS}
# )


add_custom_target(
	run_benchmark
	COMMAND benchmark_Solutions
)