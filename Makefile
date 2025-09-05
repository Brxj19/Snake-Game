# Compiler
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -I/opt/homebrew/include -Iincludes

# Linker flags
LDFLAGS := -L/opt/homebrew/lib
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
BIN := $(BIN_DIR)/game

# Files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Default target
all: $(BIN)

$(BIN): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Cleanup
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
