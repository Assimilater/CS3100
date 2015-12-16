assign5: bin/pcthread.o bin/main.o
	g++ bin/*.o -o assign5 -pthread

bin/main.o: src/main.cpp src/pcthread.hpp src/pQueue.hpp
	mkdir -p bin
	g++ -std=c++11 -c src/main.cpp -o bin/main.o

bin/pcthread.o: src/pcthread.hpp src/pcthread.cpp src/pQueue.hpp
	mkdir -p bin
	g++ -std=c++11 -c src/pcthread.cpp -o bin/pcthread.o

clean:
	rm bin/*
	rm assign5
