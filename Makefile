
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
	rm -rf build-win/

build_tests/:
	cmake -DTEST=ON -B build_tests/

tests: build_tests/ compile_tests

run_tests:
	./build_tests/main

compile_tests:
	make -C build_tests/ -j$(nproc)

dump: build/
	objdump -M intel -S -d build/main> dump.txt

build-win/:
	cmake -DCMAKE_TOOLCHAIN_FILE=./linux_cc_windows.cmake -B build-win

win: build-win/
	make -C build-win/ -j$(nproc)


.PHONY: all clean run compile dump compile_tests, tests, run_tests
