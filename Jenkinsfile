/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh '''#!/bin/bash
                      cd projects/cpp/code_analysis && make clang-tidy
                '''
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage ('Extract test results') {
            steps {
                publishCoverage adapters: [cobertura('**/projects/cpp/code_analysis/build/example_cobertura_summary.xml')]
            }
        }
    }
    post {
        always {
            junit '**/projects/cpp/code_analysis/build/junit.xml'
        }
    }
}


