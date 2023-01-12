#!/bin/bash

# base directory needs to be mounted at same location as on host for dod (docker out of docker)
abs_root_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")/../"; pwd)"/"
result_dir=$abs_root_dir"projects/.results"

if [ $# -eq 0 ]; then
  echo "Pass at least one existing directory"
  echo "Exit!"
  exit 128 
fi

csv_make_dirs=$(cd $abs_root_dir/.docker; ./find_make_directories.sh $@)
cppcheck_dirs=$(echo "$csv_make_dirs" | sed -r 's/[,]+/ /g')
echo $cppcheck_dirs

for dir in $cppcheck_dirs
do
  find ${abs_root_dir}${dir}"/src" | grep "\.hpp" >> ${abs_root_dir}projects/cpp_file_list
  find ${abs_root_dir}${dir}"/src" | grep "\.cpp" >> ${abs_root_dir}projects/cpp_file_list
  find ${abs_root_dir}${dir}"/test" | grep "\.cpp" >> ${abs_root_dir}projects/cpp_file_list
done
cat ${abs_root_dir}projects/cpp_file_list

run_cmd=${abs_root_dir}/.docker/run_docker.sh
${run_cmd} "if ! [ -d "${result_dir}" ]; then mkdir ${result_dir}; fi"
${run_cmd} "cd ${abs_root_dir}; cppcheck --check-config --xml --xml-version=2 --file-list=${abs_root_dir}projects/cpp_file_list 2> ${result_dir}/cppcheck_config.xml"
${run_cmd} "cd ${abs_root_dir}; cppcheck --force --verbose --enable=all --suppress=missingIncludeSystem --xml --xml-version=2 --file-list=${abs_root_dir}projects/cpp_file_list 2> ${result_dir}/cppcheck.xml"

rm ${abs_root_dir}projects/cpp_file_list
