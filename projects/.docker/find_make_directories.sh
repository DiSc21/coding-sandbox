#!/bin/bash

cwd=$(pwd)

mwd=$(pwd)
if [ $# -eq 1 ]; then
  if ! [ -d "$1" ]; then
    echo "No directory "$1" found."
    echo "Exit!"
    exit 1
  fi
  cd $1
  mwd=$(pwd)
fi

make_dirs=$(find . -type f -name "Makefile" -exec dirname "{}" \; | sort -u | grep -v "/build\>")

for make_dir in $make_dirs
do
  cd $make_dir;
  make
  cd $mwd
done

cd $cwd
