CXX 		= g++
CXXFLAGS 	= -I. -I$(LIB_DIR)

LIB_DIR 	= ./lib
HEADERS		= cxxopts.hpp 
OBJECTS		= main.o test.o
TARGET		= main

.PHONY: clean

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS)

main.o: main.cc
	$(CXX) $(CXXFLAGS) -o $@ -c main.cc

test.o: test.cc
	$(CXX) $(CXXFLAGS) -o $@ -c test.cc

clean:
	rm -f *.o main
