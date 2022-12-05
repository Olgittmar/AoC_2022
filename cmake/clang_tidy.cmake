# Don't analyze or format 3rd party code.
set(FILES_TMP ${FILES_TO_TIDY})
foreach(source_file ${FILES_TMP})
	string(FIND ${source_file} ${THIRD_PARTY_DIR} source_is_third_party)
	if(NOT ${source_is_third_party} EQUAL -1)
		list(REMOVE_ITEM FILES_TMP ${source_file})
	endif()
endforeach()


set(INFRASTRUCTURE_CHECK_COMMAND
	clang-check
	-p=${PROJECT_BINARY_DIR}
	${FILES_TMP}
)

set(STATIC_ANALYSIS_COMMAND
	clang-tidy
	--config-file=${PROJECT_BINARY_DIR}/../.clang-tidy
	--fix-notes
	--format-style=file
	--use-color
	-p=${PROJECT_BINARY_DIR}
	${FILES_TMP}
)

add_custom_target(
	run_clang_tidy
	COMMAND ${STATIC_ANALYSIS_COMMAND} && ${INFRASTRUCTURE_CHECK_COMMAND}
)