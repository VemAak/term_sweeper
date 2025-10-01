# Compiler to use
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -g 
LINKERFLAGS = -lncurses

# Name of the executable
TARGET = term_sweeper

# Source files (all .c files in the current directory)
SRCS = $(wildcard *.c)

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Default target: builds the executable
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LINKERFLAGS)

# Rule to compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Phony targets (targets that don't correspond to a file)
.PHONY: clean all

# Clean target: removes object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
