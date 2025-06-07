TARGET = tinyweb

CC = gcc
CFLAGS = -Wall -g

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/tinyweb.c
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET)
