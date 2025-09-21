# add comments
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=out
# Find all C source files in the current directory and subdirectories
C_SRCS := \
    $(wildcard *.c) \
    $(wildcard src/*.c) \
    $(wildcard src/**/*.c)
# Find all header files in the current directory and subdirectories
HDRS := \
    $(wildcard *.h) \
    $(wildcard src/*.h) \
    $(wildcard src/**/*.h)
# Takes the list of sources and generates a list of object files with the same names
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))
# Default target; depends on the build target and then prints "All Done"
all: build
	@echo "All Done"
# Build target; depends on all object files being up to date. Link objects into the final executable
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)
# Compile rule for source files in the root directory, creates needed directories in bin/ to avoid cluttering src folder
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
# The compile rule for source files in the src/ directory and deeper, creates needed directories in bin/ to avoid cluttering src folder
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
# Clean target: remove the compiled binary and the bin/ directory
clean:
	rm -f $(TARGET)
	rm -rf bin
# Run target: build the project if necessary and then run the executable
run: build
	./$(TARGET) outputfile.txt
# Which target: display the list of all found source files, header files, and target object files
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "TARGET OBJS: ${OBJS}"
