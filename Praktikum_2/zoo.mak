CC = gcc
CFLAGS = -Wall -Wextra
TARGET = main
OBJS = main.o Zoo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c Zoo.h
	$(CC) $(CFLAGS) -c main.c

Zoo.o: Zoo.c Zoo.h
	$(CC) $(CFLAGS) -c Zoo.c

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
