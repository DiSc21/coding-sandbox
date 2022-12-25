PROJECT(cmake_git_version)
CMAKE_MINIMUM_REQUIRED (VERSION 3.22)

include_directories(src)

add_compile_options(-std=c++17)
find_package(GTest REQUIRED)


add_library(builder_pattern SHARED src/DS_Armor.hpp src/DS_NPC.hpp)
target_link_libraries(builder_pattern GTest::GTest GTest::Main)

ADD_EXECUTABLE(test_armor test/test_Armor.cpp)
target_link_libraries(test_armor builder_pattern GTest::GTest GTest::Main)

ADD_EXECUTABLE(test_NPC test/test_NPC.cpp)
target_link_libraries(test_NPC builder_pattern GTest::GTest GTest::Main)

enable_testing()

add_test(main_test_armor test_armor)
add_test(main_test_NPC test_NPC)

