VERSION = 1.0.0
SRC_DIR = src
MAIN_FILE = main.c
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)
OBJ_DIR = $(BUILD_DIR)/obj
DIST_DIR = $(BUILD_DIR)/dist
HEADERS = $(wildcard $(SRC_DIR)/*.h)
SOURCES = $(filter-out $(SRC_DIR)/$(MAIN_FILE), $(wildcard $(SRC_DIR)/*.c))
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))
LIB_FILE = $(BIN_DIR)/cunit.a
MAIN_OBJECT = $(patsubst %.c,$(OBJ_DIR)/%.o, $(MAIN_FILE))
APP_FILE = $(BIN_DIR)/example
TEST_DIR = test
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst %.c,$(TEST_OBJ_DIR)/%.o,$(notdir $(TEST_SOURCES)))
TESTSUITE_FILE = $(BIN_DIR)/testsuite
CC = clang
CXX = clang
CFLAGS = -ansi -Wpedantic -Wall -Wextra -Werror
LFLAGS = -lm -v

# Enable debugging
#CFLAGS += -g

build: compile resources test run check dist

run: compile
	$(APP_FILE)

resources:
	cp $(HEADERS) $(LIB_FILE) README.md LICENSE.txt $(DIST_DIR)

clean:
	rm -rf $(BUILD_DIR)

compile: prepare $(LIB_FILE) $(APP_FILE)

test: prepare $(TESTSUITE_FILE)
	$(TESTSUITE_FILE)

check:
	clang-format --dry-run -Werror --style=file --fallback-style=Google $(SRC_DIR)/* $(TEST_DIR)/*

format:
	clang-format -i --style=file --fallback-style=Google $(SRC_DIR)/* $(TEST_DIR)/*

dist: compile resources
	tar czf build/cunit-$(VERSION).tar.gz --directory=$(DIST_DIR) .

prepare:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(TEST_OBJ_DIR)
	mkdir -p $(DIST_DIR)

$(LIB_FILE): $(OBJECTS)
	ar rcs $@ $^

$(APP_FILE): $(LIB_FILE) $(MAIN_OBJECT)
	$(CC) $(LFLAGS) -o $@ $^

$(TESTSUITE_FILE): $(LIB_FILE) $(TEST_OBJECTS)
	$(CC) $(LFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<
