# Makefile

CXX = c++
CPPFLAGS = -Wall -std=c++17

TARGET := main
# options: main, (deprecated and removed) load
SOURCES_BASE = FOLD_datatypes FOLD_parse FOLD_utils
CPP_FILES = $(SOURCES_BASE:=.cpp)
H_FILES = $(SOURCES_BASE:=.h)



# default target = main
main: $(TARGET).o FOLD_datatypes.o FOLD_parse.o FOLD_utils.o
	$(CXX) $(CPPFLAGS) -o main $(TARGET).o FOLD_datatypes.o FOLD_parse.o FOLD_utils.o

$(TARGET).o: FOLD_visualize.py $(TARGET).cpp $(CPP_FILES) $(H_FILES)
	$(CXX) $(CPPFLAGS) -c $(TARGET).cpp

FOLD_datatypes.o: FOLD_datatypes.cpp FOLD_datatypes.h
	$(CXX) $(CPPFLAGS) -c FOLD_datatypes.cpp

FOLD_parse.o: FOLD_parse.cpp FOLD_parse.h
	$(CXX) $(CPPFLAGS) -c FOLD_parse.cpp

FOLD_utils.o: FOLD_utils.cpp FOLD_utils.h
	$(CXX) $(CPPFLAGS) -c FOLD_utils.cpp


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
	python3 FOLD_visualize.py
	rm out.json


.PHONY: clean trial run