#!/bin/bash

path=$(dirname "${BASH_SOURCE[0]}")
dockerfile=$path/Dockerfile

tag_long=$(sha256sum $dockerfile | awk '{ print $1 }')
tag=${tag_long::8}

name=coding_sandbox_docker
dockername="$name:$tag"

if [[ -z "${BUILD_TAG}" ]]; then
  name="${name}-$('whoami')"
else
  name="${name}-${BUILD_TAG}"
fi
name="${name/\%2F/_}"
name=$(echo "${name}" | sed -r 's/[%]+/_/g')
echo ${name}
docker images | grep $name | grep $tag -q || DOCKER_BUILDIT=1 docker build -f $dockerfile -t $dockername .

