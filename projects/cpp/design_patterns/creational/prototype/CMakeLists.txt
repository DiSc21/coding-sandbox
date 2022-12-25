PROJECT(cmake_git_version)
CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

include_directories(src)

add_compile_options(-std=c++17)
find_package(GTest REQUIRED)


add_library(prototype_pattern SHARED src/DS_Prototype.hpp)
target_link_libraries(prototype_pattern GTest::GTest GTest::Main)

ADD_EXECUTABLE(main test/test.cpp)
target_link_libraries(main prototype_pattern GTest::GTest GTest::Main)

enable_testing()

add_test(main_test main)

