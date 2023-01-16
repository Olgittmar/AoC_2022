add_subdirectory(ElfCalories)
add_subdirectory(NoSpace)
add_subdirectory(SupplyStacks)
add_subdirectory(CampCleanup)
add_subdirectory(RockPaperScissors)
add_subdirectory(RuckSack)
add_subdirectory(TuningTrouble)
add_subdirectory(TreetopTreeHouse)

# Propagate values from subdirs to parent dir
set(SOLUTIONS_LIB_SOURCES ${SOLUTIONS_LIB_SOURCES} PARENT_SCOPE)