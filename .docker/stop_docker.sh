#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh

if [[ $(docker ps | grep ${name}) ]]
then
    docker stop $name
else
    echo "No docker with name ${name} running"
fi

