CC = gcc
CFLAGS ?= -Wall -Wextra -std=c11
TARGET = task6
SRCS = task6.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) test_file