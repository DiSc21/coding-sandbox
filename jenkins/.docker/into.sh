#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh

#docker exec -it $name /bin/bash
docker exec -it $name /bin/bash -c "newgrp docker"

