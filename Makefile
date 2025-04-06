# compiler
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iinclude
DEBUG_FLAGS := -g -O0

# directory
SRC_DIR := src
OBJ_DIR := obj

# files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# binary file
TARGET := tcpip_stack

# default
all: $(TARGET)

# debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

# link
$(TARGET): $(OBJS)
	$(CC) $^ -o $@

# compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# re
re: clean all

.PHONY: all clean re
