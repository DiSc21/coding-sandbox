//*****************************************************************************************|
//     ______ _              ____            _      ,                      _               |
//    (_) |  | |            (|   \ o        | |    /|   /         o       | |              |
//        |  | |     _       |    |    ,_   | |     |__/   _  _       __, | |   _|_        |
//      _ |  |/ \   |/      _|    ||  /  |  |/_)    | \   / |/ |  |  /  | |/ \   |         |
//     (_/   |   |_/|__/   (/\___/ |_/   |_/| \_/   |  \_/  |  |_/|_/\_/|/|   |_/|_/       |
//    *****************************************************************/|***********       |
//                                                                     \|                  |
//_________________________________________________________________________________________|
//                                                                                         |
// Copyright 2023 DiSc21-Fantasies @ TDK. All rights reserved.                             |
// None of the code is licensed under any License.                                         |
//_________________________________________________________________________________________|


/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    environment {
        def make_dirs_roots = "projects/cpp/code_analysis projects/cpp/design_patterns"
        def make_dirs = sh(script: ".docker/find_make_directories.sh ${make_dirs_roots}", returnStdout: true).trim()

        // thresholds for various code analysis tools
        // ------------------------------------------
        def threshold_cppcheck_config = 51
        def threshold_unit_tests = 1
        def threshold_flawfinder = 1
        def threshold_clang_tidy = 1
        def threshold_cppcheck = 1
        def threshold_cpplint = 1
        def threshold_doxygen = 1
        def threshold_cmake = 1
        def threshold_clang = 1
        def threshold_gcc = 1
    }
    parameters {
        //choice(
        //    name: 'something_to_choose_from',
        //    choices: ['OptionA', 'OptionB', 'AndSoOn'],
        //    description: 'some choices not sure what to choose yet'
        //)
        //string(name: 'test_dir', defaultValue: 'projects/cpp', description: 'Root directory for projects to build and test')

        // boolean various code analysis stages
        // ------------------------------------
        booleanParam(name: 'unittests',  defaultValue: true, description: 'Check if unit test stage should be run')
        booleanParam(name: 'flawfinder', defaultValue: true, description: 'Check if flawfinder stage should be run')
        booleanParam(name: 'clangtidy',  defaultValue: true, description: 'Check if clang-tidy stage should be run')
        booleanParam(name: 'cppcheck',   defaultValue: true, description: 'Check if cppcheck stage should be run')
        booleanParam(name: 'cpplint',    defaultValue: true, description: 'Check if cpplint stage should be run')
        booleanParam(name: 'doxygen',    defaultValue: true, description: 'Check if doxygen stage should be run')
        booleanParam(name: 'cmake',      defaultValue: true, description: 'Check if cmake stage should be run')
        booleanParam(name: 'clang',      defaultValue: true, description: 'Check if clang stage should be run')
        booleanParam(name: 'gcc',        defaultValue: true, description: 'Check if gcc stage should be run')
    }
    stages {
        stage('Build Docker') {
            steps {
                echo 'Building Docker ...'
                sh ".docker/start_docker.sh"
                echo 'Make results directory ...'
                sh "rm -rf .results || true; mkdir .results"
                echo "Build directories: ${make_dirs}"
            }
        }
        stage('GCC/Clang Build') {
            parallel {
                stage('GCC Build') {
                    steps {
                        script {
                            "${make_dirs}".split(',').each {
                                echo "Building (gcc) of subproject ${it}"
                                sh "cd ${it} && make build/gcc"
                                sh "echo ${it}/build/gcc_build.log | xargs cat >> .results/gcc_build.log"
                                sh "echo ${it}/build/CMakeFiles/CMakeOutput.log | xargs cat  >> .results/cmake_builds.log;"
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
                                sh "echo ${it}/build_clang/clang_build.log | xargs cat  >> .results/clang_build.log;"
                            }
                        }
                    }
                }
            } // parallel
        } // stage
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
        stage('C++ Code Analysis') {
            parallel {
                stage('Cmake') {
                    when {
                        expression { return params.cmake }
                    }
                    steps {
                        echo 'Collecting CMake Warnings ...'
                        recordIssues (
                            qualityGates: [[threshold: threshold_cmake, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [cmake(pattern:'**.results/cmake_builds.log')]
                        )
                    }
                }
                stage('GCC') {
                    when {
                        expression { return params.gcc }
                    }
                    steps {
                        echo 'Collecting GCC Warnings ...'
                        recordIssues (
                            qualityGates: [[threshold: threshold_gcc, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [gcc(pattern:'**.results/gcc_build.log')]
                        )
                    }
                }
                stage('Clang') {
                    when {
                        expression { return params.clang }
                    }
                    steps {
                        echo 'Collecting Clang Warnings ...'
                        recordIssues (
                            qualityGates: [[threshold: threshold_clang, type: 'TOTAL', unstable: true]],
                            sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                            tools: [clang(pattern:'**.results/clang_build.log')]
                        )
                    }
                }
                stage('Clang-Tidy') {
                    when {
                        expression { return params.clangtidy }
                    }
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
                stage('CppCheck') {
                    when {
                        expression { return params.cppcheck }
                    }
                    steps {
                        script {
                            echo 'Running CppCheck ...'
                            sh '''#!/bin/bash
                                  .docker/run_cppcheck_on_subprojects.sh ${make_dirs_roots}
                                  cp projects/.results/cppcheck.xml .results/cppcheck.xml
                                  cp projects/.results/cppcheck_config.xml .results/cppcheck_config.xml
                            '''
                            recordIssues (
                                qualityGates: [[threshold: threshold_cppcheck_config, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [cppCheck(pattern:'**.results/cppcheck_config.xml', id: 'cppcheck-config', name: 'CppCheck Config')]
                            )
                            recordIssues (
                                qualityGates: [[threshold: threshold_cppcheck, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [cppCheck(pattern:'**.results/cppcheck.xml')]
                            )
                        }
                    }
                }
                stage('CppLint') {
                    when {
                        expression { return params.cpplint }
                    }
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
                stage('Flawfinder') {
                    when {
                        expression { return params.flawfinder }
                    }
                    steps {
                        script {
                            echo 'Collecting Flawfinder Warnings ...'
                            sh '''#!/bin/bash
                                  tmp_dirs=${make_dirs}","
                                  src_dirs=$(echo ${tmp_dirs//,//src })
                                  .docker/run_docker.sh "flawfinder --context ${src_dirs} >> .results/flawfinder.log"
                                  .docker/run_docker.sh "flawfinder --html --context ${src_dirs} >> .results/flawfinder.html"
                            '''
                            recordIssues (
                                qualityGates: [[threshold: threshold_flawfinder, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [flawfinder(pattern:'**.results/flawfinder.log')]
                            )
                        }
                    }
                }
                stage('Doxygen') {
                    when {
                        expression { return params.doxygen }
                    }
                    steps {
                        script {
                            echo 'Collecting Doxygen Warnings ...'
                            //System.setProperty("hudson.model.DirectoryBrowserSupport.CSP", "default-src 'self'; script-src 'self' 'unsafe-inline' 'unsafe-eval'; img-src 'self'; style-src 'self' 'unsafe-inline'; font-src *; sandbox allow-forms allow-scripts allow-same-origin;");
                            sh "make doxygen && cp doxygen/doxygen_warnings.log .results"
                            recordIssues (
                                qualityGates: [[threshold: threshold_doxygen, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [doxygen(pattern:'**.results/doxygen_warnings.log')]
                            )
                        }
                    }
                }
                stage('Test Results') {
                    when {
                        expression { return params.unittests }
                    }
                    steps {
                        script {
                            echo 'Collecting Test Results ...'
                            recordIssues (
                                qualityGates: [[threshold: threshold_unit_tests, type: 'TOTAL', unstable: true]],
                                sourceCodeEncoding: 'ISO-8859-1', enabledForFailure: true, aggregatingResults: true,
                                tools: [junitParser(pattern:'projects/**/Testing/main.xml', id: 'test-results', name: 'Unit-Test')]
                            )
                        }
                    }
                }
                stage('Coverage') {
                    when {
                        expression { return params.unittests }
                    }
                    steps {
                        script {
                            echo 'Running Gcovr ...'
                            sh '''#!/bin/bash
                                  .docker/run_gcovr_on_subprojects.sh ${make_dirs_roots}
                                  cp projects/.results/gcovr_coverage.xml .results/gcovr_coverage.xml
                                  cp projects/.results/gcovr_*.html .results/
                            '''
                        }
                    }
                }
            } // parallel
        } // stage
    } // stages
    post {
        always {
            echo 'Perfoming post build/check steps'
            publishCoverage adapters: [cobertura('**.results/gcovr_coverage.xml')]
            publishHTML target: ([ allowMissing: false, alwaysLinkToLastBuild: true, keepAll: true,
                                   reportDir: '.results', reportFiles: 'gcovr_coverage.html',
                                   reportName: 'Gcovr Coverage HTML-Report'])
            publishHTML target: ([ allowMissing: false, alwaysLinkToLastBuild: true, keepAll: true,
                                   reportDir: 'doxygen/html', reportFiles: 'index.html',
                                   reportName: 'Doxygen HTML-Report'])
            publishHTML target: ([ allowMissing: false, alwaysLinkToLastBuild: true, keepAll: true,
                                   reportDir: '.results', reportFiles: 'flawfinder.html',
                                   reportName: 'Flawfinder HTML-Report'])
            sh ".docker/stop_docker.sh"
        }
    }
}

