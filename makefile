all:
	cmake -B build
	cmake --build build -j8
	./build/bin/aquarius

build:
	cmake -B build
	cmake --build build -j8 --config Release

debug:
	cmake -DDebug=ON -B build
	cmake --build build -j8