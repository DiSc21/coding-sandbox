#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh

docker images | grep $name | grep $tag -q || DOCKER_BUILDIT=1 docker build -f $dockerfile -t $dockername .

