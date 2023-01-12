#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/build_docker.sh

docker run -i --rm --name ${name} \
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
    --volume /etc/passwd:/etc/passwd:ro \
    --volume /etc/group:/etc/group:ro \
    --volume /var/run/docker.sock:/var/run/docker.sock \
    --user $(id -u) \
    --net=host \
    --env="DISPLAY" \
    -v $abs_root_dir:$abs_root_dir \
    -w $(pwd) \
    $dockername /bin/bash -c "touch /ws/docker_started; $@"

