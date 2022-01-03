PROJECT(cmake_git_version)

CMAKE_MINIMUM_REQUIRED (VERSION 3.22)
add_compile_options(-std=c++17)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKMM REQUIRED gtkmm-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(src ${GTKMM_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKMM_LIBRARY_DIRS})
ADD_DEFINITIONS(${GTKMM_CFLAGS_OTHER})

# Create example gtk button window library
ADD_LIBRARY(example_gtk src/DS_HelloGTKWindow.cpp)
TARGET_LINK_LIBRARIES(example_gtk PRIVATE ${GTKMM_LIBRARIES})

# Create example gtk executable 
ADD_EXECUTABLE(main_gtk src/main.cpp)
TARGET_LINK_LIBRARIES(main_gtk example_gtk)

# Create simple gtk button gtest shell
ADD_EXECUTABLE(test_gtk test/test.cpp)
TARGET_LINK_LIBRARIES(test_gtk example_gtk GTest::GTest GTest::Main)

enable_testing()
add_test(main_test test_gtk)

