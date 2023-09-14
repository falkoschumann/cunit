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
TESTMEM_MAIN_FILE = $(TEST_DIR)/testmem.c
TESTMEM_APP_FILE = $(BIN_DIR)/runtestmem
TEST_DIR = test
TEST_MAIN_FILE = $(TEST_DIR)/tests.c
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj
TEST_SOURCES = $(filter-out $(TEST_MAIN_FILE) ${TESTMEM_MAIN_FILE}, $(wildcard $(TEST_DIR)/*.c))
TEST_OBJECTS = $(patsubst %.c,$(TEST_OBJ_DIR)/%.o,$(notdir $(TEST_SOURCES)))
TEST_APP_FILE = $(BIN_DIR)/runtests
TEST_COVERAGE_DIR = $(BUILD_DIR)/coverage
CC = clang
CXX = clang++
CFLAGS = -ansi -Wpedantic -Wall -Wextra -Werror
LFLAGS = -lm

# Enable debugging
#CFLAGS += -gdwarf-4

# Enable coverage
#TEST_CFLAGS += --coverage

build: dist $(TESTMEM_APP_FILE)

clean:
	rm -rf $(BUILD_DIR)

run: compile
	$(APP_FILE)

format:
	clang-format -i --style=file --fallback-style=Google $(SRC_DIR)/* $(TEST_DIR)/*

docker:
	docker run --rm -v "$(PWD)":/usr/src/cunit -w /usr/src/cunit silkeh/clang make

prepare:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(TEST_OBJ_DIR)
	mkdir -p $(TEST_COVERAGE_DIR)
	mkdir -p $(DIST_DIR)

compile: prepare $(LIB_FILE) $(APP_FILE)

test: compile $(TEST_APP_FILE)
	$(TEST_APP_FILE)
ifdef TEST_CFLAGS
	mv *.gcda *.gcno $(TEST_COVERAGE_DIR)
	gcov -o $(TEST_COVERAGE_DIR) $(SOURCES)
	mv *.gcov $(TEST_COVERAGE_DIR)
endif

testmem: compile $(TESTMEM_APP_FILE)
	valgrind --leak-check=yes --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./build/runtestmem

testmem_local:
	docker build -t testmem_local .
	docker run --rm -it testmem_local

verify: test
	clang-format --dry-run -Werror --style=file --fallback-style=Google $(SRC_DIR)/* $(TEST_DIR)/*

dist: verify
	cp $(HEADERS) $(LIB_FILE) README.md LICENSE.txt CHANGELOG.md $(DIST_DIR)
	tar czf build/cunit-$(VERSION).tar.gz --directory=$(DIST_DIR) .

$(LIB_FILE): $(OBJECTS)
	ar rcs $@ $^

$(APP_FILE): $(MAIN_FILE) $(LIB_FILE)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

$(TEST_APP_FILE): $(TEST_MAIN_FILE) $(TEST_OBJECTS) $(LIB_FILE)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) $(LFLAGS) -o $@ $^

$(TESTMEM_APP_FILE): $(TESTMEM_MAIN_FILE) $(LIB_FILE)
	$(CC) $(CFLAGS) $(TEST_CFLAGS) $(LFLAGS) -o $@ $^

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<
