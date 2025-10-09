CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o cycle.o
TARGET = program

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c defs.h
	$(CC) $(CFLAGS) -c main.c

cycle.o: cycle.c defs.h
	$(CC)  $(CFLAGS) -c cycle.c

clean: 
	rm -f $(OBJ) $(TARGET)