# Makefile

CXX = c++
CPPFLAGS = -Wall -std=c++17

TARGET := load
# options: main, load

# default target = main
main: $(TARGET).o storage_objects.o
	$(CXX) $(CPPFLAGS) -o main $(TARGET).o storage_objects.o

$(TARGET).o: $(TARGET).cpp storage_objects.h
	$(CXX) $(CPPFLAGS) -c $(TARGET).cpp

storage_objects.o: storage_objects.cpp storage_objects.h
	$(CXX) $(CPPFLAGS) -c storage_objects.cpp

clean:
	rm -f *.o main

run:
	make clean
	make
	./main


.PHONY: clean run