# Makefile
# Build rules for EECS 280 project 3

# Compiler
CXX = g++

# Set this at the command line using: make debug_or_optimize=<flag> <target> ...
debug_or_optimize = -O1

# Compiler flags
CXXFLAGS = --std=c++11 -Wall -Werror -pedantic -g -O0 $(debug_or_optimize) 

test: release
	./Matrix_public_test.exe
	./Image_public_test.exe
	./processing_public_tests.exe dog
	./processing_public_tests.exe crabster
	./processing_public_tests.exe horses
	./resize.exe dog.ppm dog_4x5.out.ppm 4 5
	diff dog_4x5.out.ppm dog_4x5.correct.ppm


release: Matrix_public_test.exe Matrix_tests.exe Image_public_test.exe \
		 Image_tests.exe processing_public_tests.exe resize.exe

debug: debug_or_optimize = -g
debug: Matrix_public_test.exe Matrix_tests.exe Image_public_test.exe \
	   Image_tests.exe processing_public_tests.exe resize.exe

Matrix_public_test.exe: Matrix_public_test.cpp Matrix.cpp Image.cpp test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Matrix_tests.exe: Matrix_tests.cpp Matrix.cpp Image.cpp test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Image_public_test.exe: Image_public_test.cpp Matrix.cpp Image.cpp test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

Image_tests.exe: Image_tests.cpp Matrix.cpp Image.cpp test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

processing_public_tests.exe: processing_public_tests.cpp Matrix.cpp \
							 Image.cpp processing.cpp test_helpers.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

resize.exe: resize.cpp Matrix.cpp Image.cpp processing.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -vf *.exe *.out.txt *.out.ppm

test_matrix: Matrix.cpp main.cpp
	$(CXX) $(CXXFLAGS) $^ -o test

test_image: Matrix.cpp Image.cpp
	$(CXX) $(CXXFLAGS) $^ -o test
