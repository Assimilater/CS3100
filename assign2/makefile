Assign2: bin Assign2.o Assign2e.o Assign2pi.o Assign2Fib.o
	g++ -o Assign2 bin/Assign2.o bin/Assign2e.o bin/Assign2pi.o bin/Assign2Fib.o

Assign2.o: bin Assign2.cpp Assign2e.hpp Assign2Fib.hpp Assign2pi.hpp
	g++ -std=gnu++11 -c Assign2.cpp -o bin/Assign2.o

Assign2e.o: bin Assign2e.cpp Assign2e.hpp
	g++ -std=gnu++11 -c Assign2e.cpp -o bin/Assign2e.o

Assign2pi.o: bin Assign2pi.cpp Assign2pi.hpp
	g++ -std=gnu++11 -c Assign2pi.cpp -o bin/Assign2pi.o

Assign2Fib.o: bin Assign2Fib.cpp Assign2Fib.hpp
	g++ -std=gnu++11 -c Assign2Fib.cpp -o bin/Assign2Fib.o

bin:
	mkdir -p bin

clean: bin
	rm bin/*
	rm Assign2
