/* Requires the Docker Pipeline plugin */
pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                sh '''#!/bin/bash
                      cd projects/cpp && make creational 
                '''
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}

