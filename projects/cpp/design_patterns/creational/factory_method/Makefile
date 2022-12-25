# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

build: clean test 

clang-tidy: build
	${cmd} "clang-tidy-13 -checks=cert-*,-clang-analyzer-*,-hicpp-* --export-fixes=clang-tidy-fixes --warnings-as-errors=* ./src/DS_FactoryMethod.hpp"

include ${dir}/Makefile.in
CFLAGS += -lgtest -lgtest_main -lpthread -std=c++17


