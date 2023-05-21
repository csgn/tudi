CC = gcc
CFLAGS = -Wall -Werror -fPIC
LDFLAGS = -shared

SRC_DIR = .
OBJ_DIR = .
LIB_DIR = .

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
LIBRARIES = $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/%.so, $(SOURCES))

.PHONY: all clean

all: $(LIBRARIES)

$(LIB_DIR)/%.so: $(OBJ_DIR)/%.o
	$(CC) $(LDFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/*.so
