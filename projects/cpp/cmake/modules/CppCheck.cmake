find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK 
            "--enable=all"
            "--inconclusive"
            "--force" 
            "--inline-suppr"
            "--output-file=cpp_check_report.txt"
            "--suppress=missingIncludeSystem"
            #            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
    message("-- CMAKE_CXX_CPPCHECK found: ${CMAKE_CXX_CPPCHECK}")
endif()

