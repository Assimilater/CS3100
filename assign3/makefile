shell: bin/main.o bin/split.o bin/exec.o
	g++ bin/*.o -o shell

bin/main.o: main.cpp exec.hpp
	mkdir -p bin
	g++ -std=c++11 -c main.cpp -o bin/main.o

bin/exec.o: exec.hpp exec.cpp split.hpp
	mkdir -p bin
	g++ -std=c++11 -c exec.cpp -o bin/exec.o

bin/split.o: split.hpp split.cpp
	mkdir -p bin
	g++ -std=c++11 -c split.cpp -o bin/split.o

clean:
	rm bin/*
	rm shell
