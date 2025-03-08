CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test

# Link step: create llrec-test from both object files
llrec-test: llrec-test.o llrec.o
	$(CXX) $(CXXFLAGS) llrec-test.o llrec.o -o llrec-test

# Compile llrec-test.cpp into an object file
llrec-test.o: llrec-test.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c llrec-test.cpp -o llrec-test.o

# Compile llrec.cpp into an object file
llrec.o: llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c llrec.cpp -o llrec.o

# Clean up
clean:
	rm -f *.o llrec-test *~
