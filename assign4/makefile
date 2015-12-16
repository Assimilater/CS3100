shell: bin/split.o bin/pipe.o bin/exec.o bin/main.o
	g++ bin/*.o -o shell

bin/main.o: src/main.cpp src/exec.hpp
	mkdir -p bin
	g++ -std=c++11 -c src/main.cpp -o bin/main.o

bin/exec.o: src/exec.hpp src/exec.cpp src/split.hpp
	mkdir -p bin
	g++ -std=c++11 -c src/exec.cpp -o bin/exec.o
	
bin/pipe.o: src/pipe.hpp src/pipe.cpp
	mkdir -p bin
	g++ -std=c++11 -c src/pipe.cpp -o bin/pipe.o

bin/split.o: src/split.hpp src/split.cpp
	mkdir -p bin
	g++ -std=c++11 -c src/split.cpp -o bin/split.o

clean:
	rm bin/*
	rm shell
