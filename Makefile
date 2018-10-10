all: Consola
Consola:Consola.cpp
	g++ --std=c++14 -Wall -o Consola Consola.cpp
exe:Consola.cpp
	./Consola
clean:
	rm Consola
