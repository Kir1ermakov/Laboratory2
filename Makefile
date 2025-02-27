CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TEST_FLAGS = -lgtest -lgtest_main -pthread

all: main test/runTests

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

test/runTests: test/test.cpp
	mkdir -p test
	$(CXX) $(CXXFLAGS) test/test.cpp -o test/runTests $(TEST_FLAGS)

test: test/runTests
	./test/runTests

clean:
	rm -f main test/runTests *.o

.PHONY: all test clean *.o