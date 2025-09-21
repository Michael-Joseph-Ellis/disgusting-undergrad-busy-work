CC = gcc
CFLAGS = -Wall -g
EXEC = program

all: $(EXEC)

$(EXEC): driver.o functions.o
	$(CC) $(CFLAGS) -o $@ $^

driver.o: driver.c functions.h
	$(CC) $(CFLAGS) -c driver.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

run:
	./$(EXEC) input.txt
	
clean:
	rm -f *.o $(EXEC)

