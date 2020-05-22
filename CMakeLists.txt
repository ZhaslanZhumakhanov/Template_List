cmake_minimum_required(VERSION 3.16)
project(Template_List)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/Include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/Tests)

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.hpp)

add_executable(Template_List ${HEADERS} ${SOURCES} main.cpp)

