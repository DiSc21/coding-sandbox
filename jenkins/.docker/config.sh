#!/bin/bash

path=$(dirname "${BASH_SOURCE[0]}")
dockerfile=$path/Dockerfile

tag_long=$(sha256sum $dockerfile | awk '{ print $1 }')
tag=${tag_long::8}
name=jenkins_test

dockername="$name:$tag"
