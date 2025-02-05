# Compiler and flags
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -Wall -std=c++11 -I./include -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Source files
SRC = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output binary
TARGET = test

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) -lSDL2 -lSDL2_image

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean

