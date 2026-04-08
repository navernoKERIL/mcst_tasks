CC = gcc
CFLAGS ?= -Wall -Wextra -std=c11
TARGET = task9
SRCS = task9.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)