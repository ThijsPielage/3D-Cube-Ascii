# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

# Output executable
TARGET = main

# Source files
SRC = main.cpp raster.cpp Vector3D.cpp geometry.cpp

# Object files
OBJ = main.o raster.o Vector3D.o geometry.o

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp into .o
main.o: main.cpp raster.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

raster.o: raster.cpp raster.h
	$(CXX) $(CXXFLAGS) -c raster.cpp -o raster.o

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean