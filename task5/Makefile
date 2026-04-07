CC = gcc
CFLAGS ?= -Wall -Wextra -std=c11
TARGET = task5
SRCS = task5.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)