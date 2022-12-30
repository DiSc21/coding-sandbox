/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    stages {
        stage('Build Docker') {
            steps {
                echo 'Building Docker ...'
                sh '''#!/bin/bash
                      cd projects/cpp/code_analysis && make
                '''
            }
        }
        stage('GCC/Clang Build') {
            stages {
                stage('GCC Build') {
                    steps {
                        echo 'Compiling with GCC ...'
                        sh '''#!/bin/bash
                              cd projects/cpp/code_analysis && make build/gcc
                        '''
                    }
                }
                stage('Clang Build') {
                    steps {
                        echo 'Compiling with Clang ...'
                        sh '''#!/bin/bash
                              cd projects/cpp/code_analysis && make build/clang
                        '''
                    }
                }
            }
        }
        stage('Unit Testing') {
            steps {
                echo 'Running Unit Tests  ...'
                sh '''#!/bin/bash
                      cd projects/cpp/code_analysis && make test
                '''
            }
        }
        stage('Code Quality steps') {
            stages {
                stage('Check GCC Log') {
                    steps {
                        echo 'Collecting GCC Warnings ...'
                        //warnings consoleParsers: [[parserName: '']], defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '', unHealthy: ''
                        //warnings canComputeNew: false, canResolveRelativePaths: false, categoriesPattern: '', consoleParsers: [[parserName: 'MSBuild']], defaultEncoding: '', excludePattern: '', healthy: '', includePattern: '', messagesPattern: '', unHealthy: ''
                        recordIssues sourceCodeEncoding: 'ISO-8859-1', tools: [gcc(pattern:'**/projects/cpp/code_analysis/build/gcc_build.log')]
                    }
                }
                stage('Check Clang Log') {
                    steps {
                        echo 'Collecting Clang Warnings ...'
                        recordIssues sourceCodeEncoding: 'ISO-8859-1', tools: [clang(pattern:'**/projects/cpp/code_analysis/build_clang/clang_build.log')]
                    }
                }
                stage('Check Clang-Tidy') {
                    steps {
                        echo 'Running Clang-Tidy ...'
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
                        echo 'Running Gcovr ...'
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


