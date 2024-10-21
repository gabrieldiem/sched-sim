# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Linker flags (including math library)
LDFLAGS = -lm

# All .c files in the current directory
SRCS = $(wildcard *.c)

# Output executable
TARGET = schedsimu

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule to build the program
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

format: .clang-files .clang-format
	xargs -r clang-format -i <$<

# Phony targets
.PHONY: all clean format
