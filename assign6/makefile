assign6: src/main.cpp trig-std.so trig-lookup.so
	g++ -std=c++11 src/main.cpp -o assign6 -ldl

trig-std.so: src/trigfunc.cpp
	gcc -c -fpic src/trigfunc.cpp -o trigfunc.o
	gcc -shared trigfunc.o -o trig-std.so

trig-lookup.so: src/trigtable.cpp
	gcc -c -fpic src/trigtable.cpp -o trigtable.o
	gcc -shared trigtable.o -o trig-lookup.so

clean:
	-rm *.o
	-rm *.so
	-rm assign6
