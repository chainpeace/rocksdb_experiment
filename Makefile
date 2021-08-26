CXX 		= g++
CXXFLAGS 	= -I. -I$(LIB_DIR) -g

LIB_DIR 	= ./lib
HEADERS		= cxxopts.hpp 
OBJECTS		= main.o buffer.o random_memtable.o test.o
TARGET		= main

.PHONY: clean

main: $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS)

main.o: main.cc mytime.h
	$(CXX) $(CXXFLAGS) -o $@ -c main.cc

buffer.o: buffer.cc buffer.h
	$(CXX) $(CXXFLAGS) -o $@ -c buffer.cc

random_memtable.o: random_memtable.cc random_memtable.h
	$(CXX) $(CXXFLAGS) -o $@ -c random_memtable.cc

#skiplist_memtable.o: skiplist_memtable.cc skiplist_memtable.h
#	$(CXX) $(CXXFLAGS) -o $@ -c skiplist_memtable.cc

test.o: test.cc
	$(CXX) $(CXXFLAGS) -o $@ -c test.cc

clean:
	rm -f *.o main
