# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -g

# Source file
SRC = a6.c

# Object file
OBJ = a6.o

# Output file
TARGET = a6

# Default rule to build the target
all: $(TARGET)

# Rule to compile a1.c into an object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

# Rule to build the program
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
