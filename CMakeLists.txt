cmake_minimum_required(VERSION 3.20)
project(Syn VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_library(Syn SHARED)
target_sources(Syn PRIVATE main.cpp)

add_subdirectory(Client)
add_subdirectory(Includes)

target_link_libraries(Syn PRIVATE minhook)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)