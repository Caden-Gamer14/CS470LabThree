CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = scheduleFile

all: $(TARGET)

$(TARGET): cpu_scheduling.c
	$(CC) $(CFLAGS) -o $(TARGET) cpu_scheduling.c

clean:
	rm -f $(TARGET)