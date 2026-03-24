# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

# Output executable
TARGET = main

# Source files
SRC = $(wildcard *.cpp)

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean