set(TEST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_TEST)
project(${TEST_PROJECT_NAME} CXX)

include(CTest)
find_package(GTest REQUIRED)

set(MY_TESTS "")
set(TEST_SOURCE_FILES
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/test_Solutions.cpp>"
)

# Solutions test
add_executable(test_Solutions $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/test_Solutions.cpp>)
target_compile_features(test_Solutions PUBLIC cxx_std_20)

add_dependencies(test_Solutions Solutions)
target_link_libraries(test_Solutions
	gtest::gtest
	Solutions
)

target_include_directories(test_Solutions
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/Solutions>
	$<INSTALL_INTERFACE:lib/Solutions>
)

target_include_directories(test_Solutions
	SYSTEM BEFORE
	PRIVATE ${GTest_INCLUDE_DIRS}
)

set(MY_TESTS ${MY_TESTS} test_Solutions)

#Static analysis for tests are Disabled since I can't figure out how to get clang-tidy and cppcheck to ignore GTest headers...

set(FILES_TO_FORMAT ${FILES_TO_FORMAT}
	${TEST_SOURCE_FILES}
	PARENT_SCOPE
)

# Janky way to add all test commands to a single target
set(TEST_COMMANDS "")
foreach(test_to_add ${MY_TESTS})
	add_test(NAME ${test_to_add} COMMAND ${test_to_add})
	set(TEST_COMMANDS ${TEST_COMMANDS} COMMAND ${test_to_add})
endforeach()

add_custom_target(
	run_tests
	COMMAND ${TEST_COMMANDS}
)