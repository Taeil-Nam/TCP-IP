CC      := gcc
CFLAGS  := -Wall -Wextra -g -O0 -Iinclude

SRC_DIRS := src/core src/net src/utils

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)

TARGET := tcpip_stack

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all

.PHONY: all clean re