# search base directory containing Makefile.in
dir:=$(shell dir=".."; while [ true ]; do ls $$dir | grep -q Makefile.in && break || dir="$$dir/.."; done; echo $$dir)

build: clean test 

coverage:
	${cmd} "cd build; gcovr -r ../ . --exclude-throw-branches --exclude-unreachable-branches --html --html-details -o example_html_details.html"

coverage-cobertura:
	${cmd} "cd build; gcovr -r ../ . --exclude-throw-branches --exclude-unreachable-branches --xml -o example_cobertura_summary.xml"

cpp-check:
	${cmd} "cppcheck --xml --xml-version=2 ./src/ 2> build/cppcheck.xml"

clang-tidy: build coverage-cobertura
	${cmd} "run-clang-tidy-14 -p build -header-filter=.* 2>&1 | tee -a build/clang_tidy_result; cd build; cat clang_tidy_result | sed 's/\x1B\[[0-9;]\{1,\}[A-Za-z]//g' | ../../../.docker/clang-tidy-to-junit.py /home/jarjar/Coding/DockerSandbox/projects/cpp/code_analysis/ > junit.xml"

include ${dir}/Makefile.in
CFLAGS += -lgtest -lgtest_main -lpthread -std=c++17


