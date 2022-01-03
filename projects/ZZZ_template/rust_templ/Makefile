# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

all: clean create_build_dir build_test run 

create_build_dir:
	$(cmd) "mkdir build"

build_test:
	$(cmd) "rustc ./test.rs --out-dir=./build"

run:
	$(cmd) "./build/test"

include ${dir}/Makefile.in

