# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

all: create_build_dir build_n_execute

create_build_dir:
	$(cmd) "rm -rf build; mkdir build;"

build_n_execute:
	$(cmd) "cd build; rustc ../test.rs; ./test"

include ${dir}/Makefile.in

