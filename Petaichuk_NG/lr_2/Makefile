clear: all
	rm *.o
all: graph_algorithms.o main.o
	g++ graph_algorithms.o main.o -o LabWork_2
main.o: src/main.cpp src/graph_algorithms.h
	g++ -c src/main.cpp
graph_algorithms.o: src/graph_algorithms.cpp src/graph_algorithms.h
	g++ -c src/graph_algorithms.cpp
