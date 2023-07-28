SRC_DIR = src
MAIN_FILE = main.c
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)
OBJ_DIR = $(BUILD_DIR)/obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))
CC = gcc
CXX = g++
CFLAGS = -c -ansi -Wpedantic -Wall -Wextra -Werror
LFLAGS =

# Enable debugging
#CFLAGS += -g

build: prepare $(BIN_DIR)/hello

prepare:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)

format:
	clang-format --dry-run --style=file --fallback-style=Google $(SRC_DIR)/*

$(BIN_DIR)/hello: $(OBJECTS)
	$(CC) $(LFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ $<
