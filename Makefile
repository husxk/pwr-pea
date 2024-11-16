
all: build/ compile

compile: build/
	make -C build/ -j$(nproc)

build/: 
	cmake -B build/

run:
	./build/main

clean:
	rm -rf build/
	rm -rf build_tests/

build_tests/:
	cmake -DTEST=ON -B build_tests/

tests: build_tests/ compile_tests

run_tests:
	./build_tests/main

compile_tests:
	make -C build_tests/ -j$(nproc)

dump: build/
	objdump -M intel -S -d build/main> dump.txt

.PHONY: all clean run compile dump compile_tests, tests, run_tests
