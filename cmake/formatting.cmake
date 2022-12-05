# Don't format 3rd party code.
set(FILES_TMP ${FILES_TO_FORMAT})
foreach(source_file ${FILES_TMP})
	string(FIND ${source_file} ${THIRD_PARTY_DIR} source_is_third_party)
	if(NOT ${source_is_third_party} EQUAL -1)
		list(REMOVE_ITEM FILES_TMP ${source_file})
	endif()
endforeach()

set(FORMATTING_COMMAND
	clang-format
	-style=file
	-i
	${FILES_TMP}
)

add_custom_target(
	format_project
	COMMAND ${FORMATTING_COMMAND}
	VERBATIM
)