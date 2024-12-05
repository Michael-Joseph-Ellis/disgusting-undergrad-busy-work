# Michael Ellis
# CPSC 2310 Fall 24
# mje2
# Dr. Yvon Feaster

CC = gcc
CFLAGS = -Wall -Wextra -lm

TARGET = draw_circle

SRCS = driver.c ppm.c shape.c
HDRS = ppm.h shape.h

# Default input and output files
INPUT_FILE = input.txt
OUTPUT_FILE = output.ppm

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) $(INPUT_FILE) $(OUTPUT_FILE)

clean:
	rm -f $(TARGET) *.o $(OUTPUT_FILE)