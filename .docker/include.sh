#!/bin/bash

path=$(dirname "${BAS_SOURCE[0]}")
dockerfile=$path/Dockerfile

tag_long=$(sha256sum $dockerfile | awk '{ print $1 }')
tag=${tag_long::8}
name=coding_sandbox_docker

dockername="$name:$tag"

docker images | grep $name | grep $tag -q || DOCKER_BUILDIT=1 docker build -f $dockerfile -t $dockername .

