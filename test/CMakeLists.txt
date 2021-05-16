cmake_minimum_required(VERSION 3.10)
project(CRyo C CXX)

# CRyo
enable_testing()
include(${CMAKE_SOURCE_DIR}/../CRyo.cmake)
cryo(
  IMPORT "${CMAKE_CURRENT_SOURCE_DIR}/../src/"
  EXPORT "${CMAKE_BINARY_DIR}/test/"
  INCLUDE_DIRECTORIES  "${CMAKE_CURRENT_SOURCE_DIR}/../src/" ${CMAKE_SOURCE_DIR}/../src/cryo/
)
