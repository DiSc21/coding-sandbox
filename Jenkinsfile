/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    environment {
        //def make_dirs = sh(script: "./docker/find_make_directories.sh projects/cpp/code_analysis projects/cpp/design_patterns", returnStdout: true).trim() as Integer
        def make_dirs_roots = "projects/cpp/code_analysis projects/cpp/design_patterns"
        def make_dirs = sh(script: "projects/.docker/find_make_directories.sh ${make_dirs_roots}", returnStdout: true).trim()
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
                        echo "Collecting GCC Warnings subproject ${it}"
                        sh "echo ${it}/build/gcc_build.log | xargs cat >> .results/gcc_build.log"
                        sh "echo ${it}/build_clang/clang_build.log | xargs cat  >> .results/clang_build.log;"
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
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [gcc(pattern:'**.results/gcc_build.log')]
                        )
                    }
                }
                stage('Check Clang Log') {
                    steps {
                        echo 'Collecting Clang Warnings ...'
                        recordIssues (
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [clang(pattern:'**.results/clang_build.log')]
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
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [cppCheck(pattern:'**.results/cppcheck.xml')]
                            )
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


