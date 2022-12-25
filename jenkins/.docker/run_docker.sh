#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/include.sh

docker run -d --rm --name $name \
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
    --volume /etc/passwd:/etc/passwd:ro \
    --volume /etc/group:/etc/group:ro \
    --user $(id -u) \
    --env="DISPLAY" \
    -p 8080:8080 \
    -p 50000:50000 \
    -v `pwd`/jenkins_home:/var/jenkins_home \
    -v `pwd`/../projects:/ws/projects \
    $dockername /bin/bash -c "$@"

