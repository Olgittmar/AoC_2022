# Maybe move Solutions CMakeLists.txt to Solutions folder?
set(SOLUTIONS_LIB_SOURCES
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Solutions/ElfCalories.hpp>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Solutions/ElfCalories.cpp>"
)

add_library(Solutions
	STATIC ${SOLUTIONS_LIB_SOURCES}
)

set(FILES_TO_CPP_CHECK
	${FILES_TO_CPP_CHECK}
	${SOLUTIONS_LIB_SOURCES} PARENT_SCOPE
)

set(FILES_TO_TIDY
	${FILES_TO_TIDY}
	${SOLUTIONS_LIB_SOURCES} PARENT_SCOPE
)

set(FILES_TO_FORMAT
	${FILES_TO_FORMAT}
	${SOLUTIONS_LIB_SOURCES} PARENT_SCOPE
)

add_subdirectory(Utils)
target_link_libraries(Solutions PUBLIC Utils)
get_target_property(UTILS_INCLUDE_DIRS Utils INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "UTILS_INCLUDE_DIRS: ${UTILS_INCLUDE_DIRS}")
target_include_directories(Solutions INTERFACE ${UTILS_INCLUDE_DIRS})

# Add Solutions as a library for the main project to link against
set_property(
	TARGET ${MAIN_TARGET_NAME}
	PROPERTY LINK_LIBRARIES
	${LINK_LIBRARIES} Solutions
)

target_include_directories(${MAIN_TARGET_NAME}
	PRIVATE
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Solutions>"
		"$<INSTALL_INTERFACE:lib/Solutions>"
)