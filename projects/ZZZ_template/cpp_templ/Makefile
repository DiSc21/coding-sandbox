# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

build: clean test 

code=test.cpp
include ${dir}/Makefile.in
CFLAGS += -lgtest -lgtest_main -lpthread -std=c++17

