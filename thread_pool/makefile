CFLAGS = -g -std=c++17 -Wall

all: main

main: main.o thread_pool.o
	$(CXX) $(CFLAGS) -o $@ $^

main.o: main.cpp thread_pool.hpp
	$(CXX) $(CFLAGS) -c main.cpp

thread_pool.o: thread_pool.cpp thread_pool.hpp
	$(CXX) $(CFLAGS) -c thread_pool.cpp

.PHONY: clean

clean:
	-rm -f main.o thread_pool.o