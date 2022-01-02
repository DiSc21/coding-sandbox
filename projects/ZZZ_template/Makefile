# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

code=test.cpp
include ${dir}/Makefile.in
CFLAGS += -lgtest -lgtest_main -lpthread -std=c++17

simple:
	clean_simple run_simple

clean_simple:
	$(cmd) "rm -f test_build_with_makefile"

run_simple: test_build_with_makefile
	$(cmd) ./$^

test_build_with_makefile: test.cpp
	$(cmd) "$(CXX) $^ $(CFLAGS) -o $@"

