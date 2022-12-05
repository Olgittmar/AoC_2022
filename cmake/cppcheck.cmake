# Don't analyze or format 3rd party code.
set(FILES_TMP ${FILES_TO_CPP_CHECK})
foreach(source_file ${FILES_TMP})
	string(FIND ${source_file} ${THIRD_PARTY_DIR} source_is_third_party)
	if(NOT ${source_is_third_party} EQUAL -1)
		list(REMOVE_ITEM FILES_TMP ${source_file})
	endif()
endforeach()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/cppcheck)

set(STATIC_ANALYSIS_COMMAND
	cppcheck
	--cppcheck-build-dir=${CMAKE_BINARY_DIR}/cppcheck
	--project=${CMAKE_BINARY_DIR}/compile_commands.json
	--suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck_suppressions_list
)

add_custom_target(
	run_cppcheck
	COMMAND ${STATIC_ANALYSIS_COMMAND}
)