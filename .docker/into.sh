#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/build_docker.sh

if [[ $(docker ps | grep ${name}) ]]
then
    docker exec -it $name /bin/bash
else
    docker run -it --rm --name ${name} \
        --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
        --volume /etc/passwd:/etc/passwd:ro \
        --volume /etc/group:/etc/group:ro \
        --user $(id -u) \
        --net=host \
        --env="DISPLAY" \
        -v $abs_root_dir:$abs_root_dir \
        -w $abs_root_dir \
        $dockername /bin/bash
fi


