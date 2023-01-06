#!/bin/bash

# base directory needs to be mounted at same location as on host for dod (docker out of docker)
abs_base_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")/../"; pwd)

source $(dirname "${BASH_SOURCE[0]}")/include.sh

docker run -i --rm --name ${name} \
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
    --volume /etc/passwd:/etc/passwd:ro \
    --volume /etc/group:/etc/group:ro \
    --volume /var/run/docker.sock:/var/run/docker.sock \
    --user $(id -u) \
    --net=host \
    --env="DISPLAY" \
    -v $abs_base_dir:$abs_base_dir \
    $dockername /bin/bash -c "cd $(pwd); $@"

