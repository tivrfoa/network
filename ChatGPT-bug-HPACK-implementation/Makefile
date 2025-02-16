# Compiler
CC = gcc

# Directories
SRC_DIR = .
BIN_DIR = bin

# Source files
SRCS = $(SRC_DIR)/hpack.c $(SRC_DIR)/testing-hpack.c

# Object files
OBJS = $(BIN_DIR)/hpack.o $(BIN_DIR)/testing-hpack.o

# Output binary
TARGET = $(BIN_DIR)/testing-hpack

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -O2

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)

