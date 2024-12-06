all:
	cmake -B build
	cmake --build build -j8
	./build/bin/aquarius

editor:
	cmake -DDebug=ON -B build
	cmake --build build -j8
	./build/bin/editor

build:
	cmake -B build
	cmake --build build -j8 --config Release

debug:
	cmake -DDebug=ON -B build
	cmake --build build -j8
	./build/bin/aquarius
