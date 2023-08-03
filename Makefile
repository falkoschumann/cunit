VERSION = 2.0.0
SRC_DIR = src
MAIN_FILE = $(SRC_DIR)/main.c
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)
OBJ_DIR = $(BUILD_DIR)/obj
DIST_DIR = $(BUILD_DIR)/dist
HEADERS = $(wildcard $(SRC_DIR)/*.h)
SOURCES = $(filter-out $(MAIN_FILE), $(wildcard $(SRC_DIR)/*.c))
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))
LIB_FILE = $(BIN_DIR)/cunit.a
APP_FILE = $(BIN_DIR)/example
TEST_DIR = test
TEST_MAIN_FILE = $(TEST_DIR)/tests.c
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj
TEST_SOURCES = $(filter-out $(TEST_MAIN_FILE), $(wildcard $(TEST_DIR)/*.c))
TEST_OBJECTS = $(patsubst %.c,$(TEST_OBJ_DIR)/%.o,$(notdir $(TEST_SOURCES)))
TEST_APP_FILE = $(BIN_DIR)/runtests
TEST_COVERAGE_DIR = $(BUILD_DIR)/coverage
CC = clang
CXX = clang
CFLAGS = -ansi -Wpedantic -Wall -Wextra -Werror
LFLAGS = -lm

# Enable debugging
#CFLAGS += -g

# Enable coverage
TEST_CFLAGS += --coverage

build: compile resources test check dist run

run: compile
	$(APP_FILE)

resources:
	cp $(HEADERS) $(LIB_FILE) README.md LICENSE.txt CHANGELOG.md $(DIST_DIR)

clean:
	rm -rf $(BUILD_DIR)

compile: prepare $(LIB_FILE) $(APP_FILE)

test: prepare $(TEST_APP_FILE)
	$(TEST_APP_FILE)
ifdef TEST_CFLAGS
	mv *.gcda *.gcno $(TEST_COVERAGE_DIR)
	gcov -o $(TEST_COVERAGE_DIR) $(SOURCES)
	mv *.gcov $(TEST_COVERAGE_DIR)
endif

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
	mkdir -p $(TEST_COVERAGE_DIR)
	mkdir -p $(DIST_DIR)

$(LIB_FILE): $(OBJECTS)
	ar rcs $@ $^

$(APP_FILE): $(MAIN_FILE) $(LIB_FILE)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

$(TEST_APP_FILE): $(TEST_MAIN_FILE) $(SOURCES) $(TEST_SOURCES)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) $(LFLAGS) -o $@ $^

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<
