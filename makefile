all:
	cmake -B build
	cmake --build build
	./build/bin/aquarius

build:
	cmake -B build
	cmake --build build --config Release