#!/bin/bash

# base directory needs to be mounted at same location as on host for dod (docker out of docker)
abs_root_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")/../../"; pwd)"/"
result_dir=$abs_root_dir"projects/.results"

if [ $# -eq 0 ]; then
  echo "Pass at least one existing directory"
  echo "Exit!"
  exit 128 
fi

csv_make_dirs=$(cd $abs_root_dir/projects/.docker; ./find_make_directories.sh $@)
cppcheck_dirs=$(echo "$csv_make_dirs" | sed -r 's/[,]+/src /g')
add

run_cmd=${abs_root_dir}/projects/.docker/run_docker.sh
${run_cmd} "if ! [ -d "${result_dir}" ]; then mkdir ${abs_root_dir}projects/.results; fi"
${run_cmd} "cd ${abs_root_dir}; cppcheck --xml --xml-version=2 ${cppcheck_dirs} 2> ${result_dir}/cppcheck.xml"

