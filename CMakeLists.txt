cmake_minimum_required(VERSION 3.15)

project(ConvolutedBaseProject VERSION 0.1 LANGUAGES CXX)

set(MAIN_TARGET_NAME ${PROJECT_NAME}_main)

include(cmake/project_settings.cmake)

# QoL stuff to keep track of source and header files
# TODO: This has got to be possible to do prettier with CMAKE internals.
set(MAIN_SOURCE_FILES "")
set(MAIN_HEADER_FILES "")
set(FILES_TO_FORMAT "")
set(FILES_TO_TIDY "")
set(FILES_TO_CPP_CHECK "")
set(CONFIG_FILES "")
set(DATA_FILES "")

add_executable(${MAIN_TARGET_NAME} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>)
set(FILES_TO_TIDY ${FILES_TO_TIDY} "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>")
set(FILES_TO_CPP_CHECK ${FILES_TO_CPP_CHECK} "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>")
set(FILES_TO_FORMAT ${FILES_TO_FORMAT} "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/main.cpp>")

add_subdirectory(src)

target_precompile_headers(${MAIN_TARGET_NAME} PUBLIC ${MAIN_HEADER_FILES})

target_sources(${MAIN_TARGET_NAME}
	PRIVATE ${MAIN_HEADER_FILES}
	PRIVATE ${MAIN_SOURCE_FILES}
)

if(${PROJECT_NAME}_ENABLE_TESTING)
	add_subdirectory(test)
endif()

include(cmake/formatting.cmake)
include(cmake/clang_tidy.cmake)
include(cmake/cppcheck.cmake)

message("Install dir: ${CMAKE_INSTALL_PREFIX}")

install(
	TARGETS ${MAIN_TARGET_NAME}
	DESTINATION "$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/bin>"
)

install(
	FILES ${CONFIG_FILES}
	DESTINATION "$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/config>"
)

install(
	FILES ${DATA_FILES}
	DESTINATION	"$<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/data>"
)