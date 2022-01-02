#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/include.sh

docker run -it --rm --name coding_sandbox_docker \
    -v `pwd`:/ws/ \
   $dockername /bin/bash -c "$@"

