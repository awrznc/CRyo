cmake_minimum_required(VERSION 3.10)
project(CRyo C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_STANDARD 17)

add_executable(cryo src/main.cc src/cryo/cryo.cc src/cryo/generator.cc)
target_include_directories(cryo PUBLIC src/cryo/)
target_link_libraries(cryo stdc++fs)

# Test
enable_testing()

## success
add_test( NAME cryo_version_test COMMAND $<TARGET_FILE:cryo> "--version" )
set_tests_properties(cryo_version_test PROPERTIES PASS_REGULAR_EXPRESSION "cryo \\(CRyo\\) .+\\..+\\..+")

add_test( NAME cryo_short_version_test COMMAND $<TARGET_FILE:cryo> "-v" )
set_tests_properties(cryo_short_version_test PROPERTIES PASS_REGULAR_EXPRESSION "cryo \\(CRyo\\) .+\\..+\\..+")

add_test( NAME cryo_help_test COMMAND $<TARGET_FILE:cryo> "--help" )
set_tests_properties(cryo_help_test PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.+Options:")

add_test( NAME cryo_short_help_test COMMAND $<TARGET_FILE:cryo> "-h" )
set_tests_properties(cryo_short_help_test PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.+Options:")

add_test( NAME cryo_io_test COMMAND $<TARGET_FILE:cryo> "--import" "${CMAKE_CURRENT_SOURCE_DIR}/src/" "--export" "${CMAKE_BINARY_DIR}/test_tmp/" )
set_tests_properties(cryo_io_test PROPERTIES PASS_REGULAR_EXPRESSION "(\\[INFO\\] import:.+)+(\\[INFO\\] export:.+)+")

## error
add_test( NAME cryo_not_found_path_test COMMAND $<TARGET_FILE:cryo> "--import" "xxxxxxxxxxxxx" "--export" "${CMAKE_BINARY_DIR}/test_tmp/" )
set_tests_properties(cryo_not_found_path_test PROPERTIES PASS_REGULAR_EXPRESSION "import path is not found.")

add_test( NAME cryo_not_found_src_test COMMAND $<TARGET_FILE:cryo> "--import" "${CMAKE_CURRENT_SOURCE_DIR}/.github" "--export" "${CMAKE_BINARY_DIR}/test_tmp/" )
set_tests_properties(cryo_not_found_src_test PROPERTIES PASS_REGULAR_EXPRESSION "c source is not found. no work to do.")

add_test( NAME cryo_not_option_test COMMAND $<TARGET_FILE:cryo> )
set_tests_properties(cryo_not_option_test PROPERTIES PASS_REGULAR_EXPRESSION "the options is required: \\[import, export\\]")

add_test( NAME cryo_unrecognized_option_test COMMAND $<TARGET_FILE:cryo> "--xxxxxxxxxxxxx")
set_tests_properties(cryo_unrecognized_option_test PROPERTIES PASS_REGULAR_EXPRESSION "unrecognized option")


# Install
install( TARGETS cryo DESTINATION bin )
install( FILES ${CMAKE_SOURCE_DIR}/CRyo.cmake DESTINATION share/cmake/cryo/ )

# CPack
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "awrznc")
set(CPACK_PACKAGE_FILE_NAME "CRyo")
set(CPACK_PACKAGE_VERSION  "0.0.4")
include(CPack)
