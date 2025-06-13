CC = gcc
CFLAGS = -Iinclude -Wall -g

#  Use wildcard to include all .c files
SRCS = $(wildcard src/functions/userFunctions/*.c) $(wildcard src/functions/systemFunctions/*.c) $(wildcard src/functions/roleFunctions/*.c) $(wildcard src/functions/oauthFunctions/*.c) $(wildcard src/functions/defaultSetup/*.c)  $(wildcard src/functions/otherFunctions/*.c) $(wildcard src/globalVariables/*.c) $(wildcard src/*.c)

# Create object files from the source files
OBJS = $(SRCS:.c=.o)
# OBJS = $*(patsubst %.c, build/%.o, $(subst src/,,$(SRCS))

TARGET = ./build/unicambio

# Default target
all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile .c files to .o files

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
 clean-all:
	rm -f $(OBJS) $(TARGET)

# Clean target to remove the executable only
clean-exec:
	rm -f $(TARGET)

# Clean target to remove object files only
clean-obj:
	rm -f $(OBJS)