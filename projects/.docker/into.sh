#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/include.sh

docker run -it --rm --name coding_sandbox_docker \
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
    --net=host \
    --env="DISPLAY" \
    -v `pwd`:/ws/ \
    $dockername bash

