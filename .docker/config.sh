#!/bin/bash

path=$(dirname "${BASH_SOURCE[0]}")

abs_root_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")/../"; pwd)
run_cmd=${abs_root_dir}/.docker/run_docker.sh

dockerfile=$path/Dockerfile

tag_long=$(sha256sum $dockerfile | awk '{ print $1 }')
tag=${tag_long::8}

name=coding_sandbox_docker
dockername="$name:$tag"

# append jenkins build name to container name and user name otherwise
# note: this allows to have jenkins ans local builds running at the same time with different container names
if [[ -z "${BUILD_TAG}" ]]; then
  name="${name}-$('whoami')"
else
  name="${name}-${BUILD_TAG}"
fi
name="${name/\%2F/_}"
name=$(echo "${name}" | sed -r 's/[%]+/_/g')

