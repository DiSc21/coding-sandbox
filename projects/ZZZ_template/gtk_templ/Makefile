# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

all: build run

build: clean test 

run:
	${cmd} "./build/main_gtk"

include ${dir}/Makefile.in
CFLAGS += -lgtest -lgtest_main -lpthread -std=c++17

