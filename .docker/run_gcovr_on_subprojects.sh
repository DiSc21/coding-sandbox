#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh

result_dir=$abs_root_dir"/projects/.results"
if ! [ $# -eq 1 ]; then
  echo "Pass at least one existing directory"
  echo "Exit!"
  exit 128
elif ! [ -d "$abs_root_dir/$@" ]; then
  echo "No directory "$abs_root_dir"/"$@" found."
  echo "Exit!"
  exit 128
fi

csv_make_dirs=$(cd $abs_root_dir/.docker; ./find_make_directories.sh $@)

gcovr_filter_string=$(echo "$csv_make_dirs" | sed -r 's/[,]+/ --filter /g')
gcovr_exclude_string=$(echo "$csv_make_dirs" | sed -r 's/[,]+/\/test --exclude /g')
gcovr_exclude_string=$gcovr_exclude_string"/test"

gcovr_exclude_flags="--exclude-throw-branches --exclude-unreachable-branches"

gcovr_flags="--filter ${gcovr_filter_string} --exclude ${gcovr_exclude_string} ${gcovr_exclude_flags}"

${run_cmd} "if ! [ -d "${result_dir}" ]; then mkdir ${result_dir}; fi"
${run_cmd} "cd ${abs_root_dir}; gcovr -r $@ ${gcovr_flags} -v --html --html-details -o ${result_dir}/gcovr_coverage.html"
${run_cmd} "cd ${abs_root_dir}; gcovr -r $@ ${gcovr_flags} -v --xml -o ${result_dir}/gcovr_coverage.xml"

