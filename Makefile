CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/memory_manager.c
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/memory_manager.o

TARGET = bellek_yoneticisi

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean