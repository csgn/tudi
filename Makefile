CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-LSDL2 -LSDL2_image
LDLIBS=-lSDL2 -lSDL2_image

SRC_DIR=./tudi/src
BUILD_DIR=./build

SRCS=$(shell find $(SRC_DIR) -name '*.c')
OBJS=$(SRCS:%=$(BUILD_DIR)/%.o)
TARGET=binary

$(BUILD_DIR)/$(TARGET): $(OBJS)
	echo $(SRCS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDLIBS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)


export GAME_DIR=./game
