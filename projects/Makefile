# search base directory containing Makefile.in
base_dir:=$(shell dir="."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

.PHONY: default
default: build/docker

.PHONY: doxygen 
doxygen:
	${cmd} "doxygen Doxyfile"

include ${base_dir}/Makefile.in

