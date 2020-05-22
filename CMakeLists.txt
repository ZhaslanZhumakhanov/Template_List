cmake_minimum_required(VERSION 3.16)
project(Template_List)

set(CMAKE_CXX_STANDARD 14)

add_executable(Template_List main.cpp include/Array_List.hpp include/Linked_List.hpp include/Test_ArrayList.hpp include/Test_LinkedList.hpp)