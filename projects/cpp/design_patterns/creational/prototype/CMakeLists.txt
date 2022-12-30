PROJECT(cmake_git_version)
CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1 -Wall -Wextra -Wpedantic")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

include(${CMAKE_SOURCE_DIR}/cmake/modules/CppCheck.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/ClangTidy.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/modules/CodeCoverage.cmake)

message("-- CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message("-- CMAKE_CXX_FLAGS found: ${CMAKE_CXX_FLAGS}")

include_directories(src)

add_compile_options(-std=c++17)
find_package(GTest REQUIRED)


add_library(prototype_pattern SHARED src/DS_Prototype.cpp)
target_link_libraries(prototype_pattern GTest::GTest GTest::Main)

ADD_EXECUTABLE(main test/test.cpp)
target_link_libraries(main prototype_pattern GTest::GTest GTest::Main)

enable_testing()

add_test(main_test main)

