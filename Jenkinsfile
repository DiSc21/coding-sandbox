/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    environment {
        //def make_dirs = sh(script: "./docker/find_make_directories.sh projects/cpp/code_analysis projects/cpp/design_patterns", returnStdout: true).trim() as Integer
        def make_dirs_roots = "projects/cpp/code_analysis projects/cpp/design_patterns"
        def make_dirs = sh(script: "projects/.docker/find_make_directories.sh ${make_dirs_roots}", returnStdout: true).trim()
        def threshold_clang_tidy = 1
        def threshold_cppcheck = 2
        def threshold_cpplint = 7
        def threshold_doxygen = 126
        def threshold_cmake = 1
        def threshold_clang = 1
        def threshold_gcc = 1
    }
    stages {
        stage('Build Docker') {
            steps {
                echo 'Building Docker ...'
                echo "${make_dirs}"
                sh '''#!/bin/bash
                      cd projects/.docker; ./run_docker.sh "echo hello docker"
                '''
            }
        }
        stage('GCC/Clang Build') {
            stages {
                stage('GCC Build') {
                    steps {
                        script {
                            "${make_dirs}".split(',').each {
                                echo "Building (gcc) of subproject ${it}"
                                sh "cd ${it} && make build/gcc"
                            }
                        }
                    }
                }
                stage('Clang Build') {
                    steps {
                        script {
                            "${make_dirs}".split(',').each {
                                echo "Building (clang) of subproject ${it}"
                                sh "cd ${it} && make build/clang"
                            }
                        }
                    }
                }
            }
        }
        stage('Unit Testing') {
            steps {
                script {
                    "${make_dirs}".split(',').each {
                        echo "Unit testing of subproject ${it}"
                        sh "cd ${it} && make test"
                    }
                }
            }
        }
        stage('Collect Build Data') {
            steps {
                script {
                    sh "rm -rf .results || true; mkdir .results"
                    "${make_dirs}".split(',').each {
                        echo "Collecting GCC logs for subproject ${it}"
                        sh "echo ${it}/build/gcc_build.log | xargs cat >> .results/gcc_build.log"
                        echo "Collecting Clang logs for subproject ${it}"
                        sh "echo ${it}/build_clang/clang_build.log | xargs cat  >> .results/clang_build.log;"
                        echo "Collecting Clang logs for subproject ${it}"
                        sh "echo ${it}/build/CMakeFiles/CMakeOutput.log | xargs cat  >> .results/cmake_builds.log;"
                    }
                }
            }
        }
        stage('Code Quality steps') {
            stages {
                stage('Check GCC Log') {
                    steps {
                        echo 'Collecting GCC Warnings ...'
                        recordIssues (
                            qualityGates: [[threshold: threshold_gcc, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [gcc(pattern:'**.results/gcc_build.log')]
                        )
                    }
                }
                stage('Check Clang Log') {
                    steps {
                        echo 'Collecting Clang Warnings ...'
                        recordIssues (
                            qualityGates: [[threshold: threshold_clang, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [clang(pattern:'**.results/clang_build.log')]
                        )
                    }
                }
                stage('Check Cmake') {
                    steps {
                        echo 'Collecting CMake Warnings ...'
                        recordIssues (
                            qualityGates: [[threshold: threshold_cmake, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [cmake(pattern:'**.results/cmake_builds.log')]
                        )
                    }
                }
                stage('Check Clang-Tidy') {
                    steps {
                        script {
                            echo 'Running Clang-Tidy ...'
                            "${make_dirs}".split(',').each {
                                sh "cd ${it} && make clang-tidy"
                                sh "echo ${it}/build/clang_tidy_result | xargs cat  >> .results/clang_tidy_result"
                            }
                        }
                        recordIssues (
                            qualityGates: [[threshold: threshold_clang_tidy, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [clangTidy(name: 'Clang-Tidy', pattern: '**.results/clang_tidy_result')]
                        )
                    }
                }
                stage('Check CppCheck') {
                    steps {
                        script {
                            echo 'Running CppCheck ...'
                            sh '''#!/bin/bash
                                  projects/.docker/run_cppcheck_on_subprojects.sh ${make_dirs_roots}
                                  cp projects/.results/cppcheck.xml .results/cppcheck.xml
                            '''
                            recordIssues (
                                qualityGates: [[threshold: threshold_cppcheck, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [cppCheck(pattern:'**.results/cppcheck.xml')]
                            )
                        }
                    }
                }
                stage('Check CppLint') {
                    steps {
                        script {
                            echo 'Running CppStyle ...'
                            "${make_dirs}".split(',').each {
                                sh "cd ${it} && make cpplint"
                                sh "echo ${it}/build/cpplint.log | xargs cat  >> .results/cpplint.log"
                            }
                            recordIssues (
                                qualityGates: [[threshold: threshold_cpplint, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [cppLint(pattern:'**.results/cpplint.log')]
                            )
                        }
                    }
                }
                stage('Check Doxygen') {
                    steps {
                        script {
                            echo 'Collecting Doxygen Warnings ...'
                            //System.setProperty("hudson.model.DirectoryBrowserSupport.CSP", "default-src 'self'; script-src 'self' 'unsafe-inline' 'unsafe-eval'; img-src 'self'; style-src 'self' 'unsafe-inline'; font-src *; sandbox allow-forms allow-scripts allow-same-origin;");
                            sh "cd projects/ && make doxygen && cp doxygen/doxygen_warnings.log ../.results" 
                            recordIssues (
                                qualityGates: [[threshold: threshold_doxygen, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [doxygen(pattern:'**.results/doxygen_warnings.log')]
                            )
                            publishHTML target: ([ allowMissing: false,
                                                   alwaysLinkToLastBuild: true,
                                                   keepAll: true,
                                                   reportDir: 'projects/doxygen/html',
                                                   reportFiles: 'index.html',
                                                   reportName: 'Doxygen HTML-Report'
                                                ])
                        }
                    }
                }
                stage('Check Code Coverage') {
                    steps {
                        script {
                            echo 'Running Gcovr ...'
                            sh '''#!/bin/bash
                                  projects/.docker/run_gcovr_on_subprojects.sh ${make_dirs_roots}
                                  cp projects/.results/gcovr_coverage.xml .results/gcovr_coverage.xml
                                  cp projects/.results/gcovr_*.html .results/
                            '''
                            publishCoverage adapters: [cobertura('**.results/gcovr_coverage.xml')]
                            publishHTML target: ([ allowMissing: false,
                                                   alwaysLinkToLastBuild: true,
                                                   keepAll: true,
                                                   reportDir: '.results',
                                                   reportFiles: 'gcovr_coverage.html',
                                                   reportName: 'Gcovr Coverage html-Report'
                                                ])
                        }
                    }
                }
            }
        }
    }
}


