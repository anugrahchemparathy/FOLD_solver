# Makefile

CXX = c++
CPPFLAGS = -Wall -std=c++17

# default target = main
main: main.o
	$(CXX) $(CPPFLAGS) -o main main.o

main.o: main.cpp
	$(CXX) $(CPPFLAGS) -c main.cpp

clean:
	rm -f *.o main

run:
	make clean
	make
	./main


.PHONY: clean run