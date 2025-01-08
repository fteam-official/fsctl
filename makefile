all: build-bin

target:
	mkdir -p target

temp:
	mkdir -p temp

build: temp
	clang++ -c src/main.cpp -o temp/fsctl.o

build-bin: target build
	clang++ temp/fsctl.o -o target/fsctl

install: build-bin
	sudo cp target/fsctl /usr/local/bin/fsctl