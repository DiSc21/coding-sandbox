dir:=$(shell dir="."; echo $$dir)
cmd=${dir}/.docker/run_docker.sh

jenkins_docker_name="jenkins_test"

start:
	${cmd} "jenkins.sh"

restart: stop start

stop:
	docker stop jenkins_test

.PHONY: clean into

into:
	${dir}/.docker/into.sh

clean:
	${cmd} "rm -rf /var/jenkins_home"

