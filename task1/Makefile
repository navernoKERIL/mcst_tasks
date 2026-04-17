CC = gcc
CFLAGS ?= -Wall -Wextra -std=c11 -pthread
TARGET = task1
SRCS = task1.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	@echo "5 2 8 1 9 3 7 4 6" | ./$(TARGET) 4