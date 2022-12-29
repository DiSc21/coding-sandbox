/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh '''#!/bin/bash
                      cd projects/cpp/code_analysis && make
                '''
            }
        }
        stage('Code Quality steps') {
            stages {
                stage('Check Clang-Tidy') {
                    steps {
                        echo 'Running Clang-tidy ...'
                        sh '''#!/bin/bash
                              cd projects/cpp/code_analysis && make clang-tidy
                        '''
                        recordIssues enabledForFailure: true, aggregatingResults: true, tools: [clangTidy(name: 'Clang-Tidy', pattern: '**/projects/cpp/code_analysis/build/clang_tidy_result')]
                    }
                }
                stage('Check CppCheck') {
                    steps {
                        echo 'Running CppCheck ...'
                        sh '''#!/bin/bash
                              cd projects/cpp/code_analysis && make cpp-check
                        '''
                        recordIssues sourceCodeEncoding: 'ISO-8859-1', tools: [cppCheck(pattern:'**/projects/cpp/code_analysis/build/cppcheck.xml')]
                    }
                }
                stage('Check Code Coverage') {
                    steps {
                        echo 'Running gcovr ...'
                        sh '''#!/bin/bash
                              cd projects/cpp/code_analysis && make coverage-cobertura
                        '''
                        publishCoverage adapters: [cobertura('**/projects/cpp/code_analysis/build/example_cobertura_summary.xml')]
                    }
                }
            }
        }
    }
}


