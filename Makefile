
all: build/ compile

compile: build/
	make -C build/ -j$(nproc)

build/: 
	cmake -B build/

run:
	./build/main

clean:
	rm -rf build/

dump: build/
	objdump -M intel -S -d build/main> dump.txt

.PHONY: all clean run compile dump
