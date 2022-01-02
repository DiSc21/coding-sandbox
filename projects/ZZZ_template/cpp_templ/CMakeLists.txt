PROJECT(cmake_git_version)
CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

add_compile_options(-std=c++17)
find_package(GTest REQUIRED)

ADD_EXECUTABLE(main test.cpp)
target_link_libraries(main GTest::GTest GTest::Main)

enable_testing()
add_test(main_test main)

