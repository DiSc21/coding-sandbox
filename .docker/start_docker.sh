#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/build_docker.sh

if ! [[ $(docker ps | grep ${name}) ]]
then
    docker run -d --rm --name $name \
        --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
        --volume /etc/passwd:/etc/passwd:ro \
        --volume /etc/group:/etc/group:ro \
        --volume /var/run/docker.sock:/var/run/docker.sock \
        --user $(id -u) \
        --env="DISPLAY" \
        -v $(pwd):/ws \
        -w /ws \
        $dockername /bin/bash -c "touch /tmp/docker_started; sleep infinity"
else
    if [[ $(docker exec -it ${name} /bin/bash -c "test -e /tmp/docker_started && echo ${safe_word}") == ${safe_word}* ]]
    then
        echo "[INFO] Docker was already started. If you want to restart call 'make restart'"
    else
        echo "[INFO] Docker is currently in a temporary state of existance."
        echo "[INFO] Probably some make command started it for some task."
        echo "[INFO] You can wait for a short time and try again or call 'make restart'"
    fi
fi

