# Makefile for finding unique substrings using std::set

CXX = g++
CXXFLAGS = -Wall -std=c++17

# Target to compile and link the program
unique_substrings: main.o
	$(CXX) $(CXXFLAGS) -o Maze main.o

# Compile the object file for main.cpp
unique_substrings.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean up the compiled files
clean:
	rm -f *.o Maze
