function(cryo)
  cmake_parse_arguments(CRYO "" "IMPORT;EXPORT" "INCLUDE_DIRECTORIES" ${ARGN})
  execute_process(
    COMMAND cryo --import "${CRYO_IMPORT}" --export "${CRYO_EXPORT}"
  )

  file(GLOB_RECURSE GENERATED_FILE_LIST "${CRYO_EXPORT}*")

  foreach(GENERATED_FILE ${GENERATED_FILE_LIST})
    get_filename_component(GENERATED_TEST ${GENERATED_FILE} NAME_WE)
    add_executable( ${GENERATED_TEST} ${GENERATED_FILE} )
    target_include_directories(${GENERATED_TEST} PUBLIC ${CRYO_INCLUDE_DIRECTORIES})

    enable_testing()
    get_filename_component(GENERATED_TEST_TARGET ${GENERATED_FILE} DIRECTORY)
    add_test( NAME "${GENERATED_TEST_TARGET}:${GENERATED_TEST}" COMMAND $<TARGET_FILE:${GENERATED_TEST}> )
  endforeach(GENERATED_FILE)
endfunction(cryo)
