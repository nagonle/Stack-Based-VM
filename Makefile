all: clean build run

run:
    build/vm_code trace

build:
    mkdir -p build
        g++ -std=c++11 -Wall -g vm_code.cpp -o build/vm_code

clean:
    @ rm -rf build
