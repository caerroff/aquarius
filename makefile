all:
	cmake -B build
	cmake --build build

build:
	cmake -B build
	cmake --build build --config Release