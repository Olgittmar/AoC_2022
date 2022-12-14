configure_file(Utils.pc.in Utils.pc @ONLY)

# Add sources as needed
set(UTILS_LIB_SOURCES
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Definitions.hpp>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DataBroker/DataBroker.hpp>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DataBroker/DataBroker.cpp>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SelectSolution/SelectSolution.hpp>"
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SelectSolution/SelectSolution.cpp>"
)

set(UTILS_INTERFACE_SOURCES
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp>"
)

# Static source lib
add_library(Utils_lib STATIC ${UTILS_LIB_SOURCES})

# Add lib files for static analysis
set(FILES_TO_CPP_CHECK ${FILES_TO_CPP_CHECK} ${UTILS_LIB_SOURCES} PARENT_SCOPE)
set(FILES_TO_TIDY ${FILES_TO_TIDY} ${UTILS_LIB_SOURCES} PARENT_SCOPE)
set(FILES_TO_FORMAT ${FILES_TO_FORMAT} ${UTILS_LIB_SOURCES} PARENT_SCOPE)

target_include_directories(
	Utils_lib BEFORE PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>"
)

# Public interface lib
add_library(Utils SHARED ${UTILS_INTERFACE_SOURCES})

set_target_properties(
	Utils
	PROPERTIES
	PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp"
)

target_include_directories(
	Utils INTERFACE
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>"
	"$<INSTALL_INTERFACE:lib/>"
)

target_link_libraries(
	Utils Utils_lib
)

install(
	TARGETS Utils
	LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
)

install(
	FILES "${CMAKE_BINARY_DIR}/src/Utils/Utils.pc"
	DESTINATION "${CMAKE_INSTALL_PREFIX}/config"
)