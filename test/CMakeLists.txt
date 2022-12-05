set(TEST_PROJECT_NAME ${CMAKE_PROJECT_NAME}_TEST)
project(${TEST_PROJECT_NAME} CXX)

include(CTest)
find_package(GTest REQUIRED)

set(MY_TESTS "")

# Hello test
add_executable(test_Hello $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/test_Hello.cpp>)
target_compile_features(test_Hello PUBLIC cxx_std_20)

add_dependencies(test_Hello Hello)
target_link_libraries(test_Hello
	gtest::gtest
	Hello
)

target_include_directories(test_Hello
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/Hello>
	$<INSTALL_INTERFACE:lib/Hello>
)

target_include_directories(test_Hello
	SYSTEM BEFORE
	PRIVATE ${GTest_INCLUDE_DIRS}
)

set(MY_TESTS ${MY_TESTS} test_Hello)

# Add all test files for cppcheck analysis and formatting
set(FILES_TO_CPP_CHECK ${FILES_TO_CPP_CHECK}
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/test_Hello.cpp>"
	PARENT_SCOPE
)

set(FILES_TO_TIDY ${FILES_TO_TIDY}
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/test_Hello.cpp>"
	PARENT_SCOPE
)

set(FILES_TO_FORMAT ${FILES_TO_FORMAT}
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/test_Hello.cpp>"
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