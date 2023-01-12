#!/bin/bash

source $(dirname "${BASH_SOURCE[0]}")/config.sh

if [ $# -eq 0 ]; then
  echo "Pass at least one existing directory"
  echo "Exit!"
  exit 128
fi

csv_dirs=""
for input_dir in "$@"
do
  # check param directory existance
  if ! [ -d "$abs_root_dir/$input_dir" ]; then
    echo "No directory "$abs_root_dir"/"$input_dir" found."
    echo "Exit!"
    exit 128
  fi

  # find all subdirectories containing Makefile
  cd $abs_root_dir"/"$input_dir
  make_dirs=$(find . -type f,l -name "Makefile" -exec dirname "{}" \; | sort -u)

  for make_dir in $make_dirs
  do
    check_dir=$(cd ${abs_root_dir}"/"${input_dir}"/"${make_dir}; pwd)
    dir_cmakelists=$check_dir"/CMakeLists.txt"

    # check if directory also contains CMakeLists.txt
    if [[ -f "$dir_cmakelists" ]]; then
        csv_dirs=$csv_dirs${check_dir#"$abs_root_dir/"}","
    fi
  done
  cd $abs_root_dir
done

# echo list of  without trailing comma
#csv_dirs=${csv_dirs::-1}
echo ${csv_dirs::-1}
