#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/build_docker.sh

if ! [[ $(docker ps | grep ${name}) ]]
then
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
        $dockername /bin/bash -c "$@"
else
    if [[ $(docker exec -i ${name} /bin/bash -c "test -e /tmp/docker_started && echo ${safe_word}") == ${safe_word}* ]]
    then
      docker exec -i ${name} /bin/bash -c "cd $(pwd); $@"
    else
        echo "[INFO] Docker is currently in a temporary state of existance."
        echo "[INFO] Probably some make command started it for some task."
        echo "[INFO] You can wait for a short time and try again or call 'make restart'"
    fi
fi
