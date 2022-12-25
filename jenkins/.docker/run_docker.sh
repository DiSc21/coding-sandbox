#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh
source $(dirname "${BASH_SOURCE[0]}")/build_docker.sh

docker run -d --rm --name $name \
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
    --volume /var/run/docker.sock:/var/run/docker.sock \
    --volume /tmp/jenkins_keys:/keys \
    --user $(id -u) \
    --env="DISPLAY" \
    -p 8080:8080 \
    -p 50000:50000 \
    -v `pwd`/jenkins_home:/var/jenkins_home \
    -v `pwd`/jenkins_ws:`pwd`/jenkins_ws \
    -v `pwd`/..:/ws \
    $dockername /bin/bash -c "$@"
