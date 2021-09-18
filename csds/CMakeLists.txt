cmake_minimum_required(VERSION 3.20)
project(csds C)



set(CMAKE_C_STANDARD 11)

add_library(csds  src/lists.c)

target_include_directories(csds
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
#include_directories(include)



add_executable(list_test tests/list_test.c)
target_link_libraries(list_test csds)