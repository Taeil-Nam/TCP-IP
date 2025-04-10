CC      := gcc

SRC_DIRS := src/core src/net src/utils
INC_DIRS := include/core include/net include/utils
INCLUDES := $(addprefix -I, $(INC_DIRS))

CFLAGS  := -Wall -Wextra -g -O0 $(INCLUDES) -pthread
LDFLAGS := -pthread

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)

TARGET := tcpip_stack

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all

.PHONY: all clean re