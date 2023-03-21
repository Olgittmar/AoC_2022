cmake_minimum_required(VERSION 3.15)

project(AoC_2022 VERSION 0.1 LANGUAGES CXX)

set(MAIN_TARGET_NAME ${PROJECT_NAME}_main)

# Set project global settings
include(cmake/project_settings.cmake)

# Debug message to double check that paths are as expected
message("Build dir: ${CMAKE_CURRENT_BINARY_DIR}")
message("Install dir: ${CMAKE_INSTALL_PREFIX}")

# QoL stuff to keep track of file paths and destinations
set(MAIN_SOURCE_FILES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>")
set(MAIN_BIN_DESTINATION "$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/bin>")
set(MAIN_DATA_FILES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data/>")
set(MAIN_DATA_FILES_DESTINATION "$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/data>")

set(CONFIG_FILES "")
set(CONFIG_FILES_DESTINATION "$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/config>")

set(TEST_DATA_FILES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test/data/>")
# Test data files are needed in build dir, I think that's the current binary dir during build time.
set(TEST_DATA_FILES_DESTINATION "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/test/data>")

set(BENCHMARK_DATA_FILES ${MAIN_DATA_FILES} ${TEST_DATA_FILES})
set(BENCHMARK_DATA_FILES_DESTINATION "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/benchmark/data>")

# Create main target
add_executable(${MAIN_TARGET_NAME} ${MAIN_SOURCE_FILES})
set(FILES_TO_TIDY ${FILES_TO_TIDY} ${MAIN_SOURCE_FILES})
set(FILES_TO_CPP_CHECK ${FILES_TO_CPP_CHECK} ${MAIN_SOURCE_FILES})
set(FILES_TO_FORMAT ${FILES_TO_FORMAT} ${MAIN_SOURCE_FILES})

# Include source files
add_subdirectory(src)

# Add test target if enabled
if(${PROJECT_NAME}_ENABLE_TESTING)
	add_subdirectory(test)
endif()

# Add benchmark target if enabled
if(${PROJECT_NAME}_ENABLE_BENCHMARK)
	add_subdirectory(benchmark)
endif()

# Static analysis and formatting
include(cmake/formatting.cmake)
include(cmake/clang_tidy.cmake)
include(cmake/cppcheck.cmake)

# Install
install(TARGETS ${MAIN_TARGET_NAME} DESTINATION ${MAIN_BIN_DESTINATION})
install(FILES ${CONFIG_FILES} DESTINATION ${CONFIG_FILES_DESTINATION})

# TODO: Install symlink to data files instead of copying files?
install(
	DIRECTORY ${MAIN_DATA_FILES}
	DESTINATION	${MAIN_DATA_FILES_DESTINATION}
	FILE_PERMISSIONS OWNER_READ
)

install(
	DIRECTORY ${TEST_DATA_FILES}
	DESTINATION	${TEST_DATA_FILES_DESTINATION}
	FILE_PERMISSIONS OWNER_READ
)

install(
	DIRECTORY ${BENCHMARK_DATA_FILES}
	DESTINATION	${BENCHMARK_DATA_FILES_DESTINATION}
	FILE_PERMISSIONS OWNER_READ
)