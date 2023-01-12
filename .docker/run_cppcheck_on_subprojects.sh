#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh
result_dir=$abs_root_dir"/projects/.results"

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
  find ${abs_root_dir}/${dir}"/src" | grep "\.hpp" >> ${abs_root_dir}/projects/cpp_file_list
  find ${abs_root_dir}/${dir}"/src" | grep "\.cpp" >> ${abs_root_dir}/projects/cpp_file_list
  find ${abs_root_dir}/${dir}"/test" | grep "\.cpp" >> ${abs_root_dir}/projects/cpp_file_list
done
cat ${abs_root_dir}/projects/cpp_file_list

#cppcheck_include="--includes-file=${abs_root_dir}/projects/cpp/.cppcheck_sys_inc"
#cppcheck_include="-I /usr/include/c++/11/ -I /usr/local/include/gtest/gtest.h"
cppcheck_include="" # adding the include directories makes cppcheck go completely nuts
cppcheck_flags="--force --verbose --xml --xml-version=2 --file-list=${abs_root_dir}/projects/cpp_file_list"

run_cmd=${abs_root_dir}/.docker/run_docker.sh
${run_cmd} "if ! [ -d "${result_dir}" ]; then mkdir ${result_dir}; fi"
${run_cmd} "cd ${abs_root_dir}; cppcheck ${cppcheck_include} --check-config ${cppcheck_flags} 2> ${result_dir}/cppcheck_config.xml"
${run_cmd} "cd ${abs_root_dir}; cppcheck ${cppcheck_include} --enable=all --suppress=missingIncludeSystem ${cppcheck_flags} 2> ${result_dir}/cppcheck.xml"

rm ${abs_root_dir}/projects/cpp_file_list
