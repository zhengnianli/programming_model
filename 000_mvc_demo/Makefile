# Makefile
CC = gcc
CFLAGS = -lpthread -lrt

SRC = main.c model.c view.c controller.c message_queue.c config.c
TARGET = mvc_demo

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)