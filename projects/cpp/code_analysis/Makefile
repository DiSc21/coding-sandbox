# search base directory containing Makefile.in
base_dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)
# search base directory containing MakefileCPP.in
cpp_incl_dir:=$(shell dir="."; while [ true ]; do ls $$dir | grep -q MakefileCPP.in && break || dir="$$dir/.."; done; echo $$dir)

.PHONY: build
build: build/main test 

include ${base_dir}/Makefile.in
include ${cpp_incl_dir}/MakefileCPP.in
CFLAGS += -lgtest -lgtest_main -lpthread -std=c++17

