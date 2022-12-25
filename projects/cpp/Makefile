dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

.PHONY: design_patterns creational

creational:
	${dir}/.docker/find_make_directories.sh "./design_patterns/creational/"

design_patterns:
	${dir}/.docker/find_make_directories.sh "./design_patterns/"

