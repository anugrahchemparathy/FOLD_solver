# Makefile

CXX = c++
CPPFLAGS = -Wall -std=c++17

TARGET := main
# options: main, load

# default target = main
main: $(TARGET).o storage_objects.o parse_FOLD.o
	$(CXX) $(CPPFLAGS) -o main $(TARGET).o storage_objects.o parse_FOLD.o

$(TARGET).o: $(TARGET).cpp storage_objects.h
	$(CXX) $(CPPFLAGS) -c $(TARGET).cpp

storage_objects.o: storage_objects.cpp storage_objects.h
	$(CXX) $(CPPFLAGS) -c storage_objects.cpp

parse_FOLD.o: parse_FOLD.cpp parse_FOLD.h
	$(CXX) $(CPPFLAGS) -c parse_FOLD.cpp


clean:
	rm -f *.o main

trial:
	make clean
	make
	./main

run:
	make clean
	make
	./main
	python3 visualize.py
	rm out.json


.PHONY: clean trial run