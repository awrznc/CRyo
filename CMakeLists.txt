cmake_minimum_required(VERSION 3.10)
project(CRyo C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_STANDARD 17)

add_executable(cryo src/main.cc)
target_link_libraries(cryo stdc++fs)

# Test
enable_testing()
add_test( NAME cryo_version_test COMMAND $<TARGET_FILE:cryo> "--version" )
set_tests_properties(cryo_version_test PROPERTIES PASS_REGULAR_EXPRESSION "CRyo")

# Install
install( TARGETS cryo DESTINATION bin )
install( FILES ${CMAKE_SOURCE_DIR}/CRyo.cmake DESTINATION share/cmake/cryo/ )

# CPack
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "awrznc")
set(CPACK_PACKAGE_FILE_NAME "CRyo")
set(CPACK_PACKAGE_VERSION  "0.0.1")
include(CPack)
