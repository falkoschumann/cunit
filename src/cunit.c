/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "cunit.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct testcase_t {
  const char *name;
  test_function_t function;
  struct testcase_t *next;
} testcase_t;

static testcase_t *first_testcase = NULL;

static unsigned int assertion_failed_count = 0;
static unsigned int run_count = 0;
static unsigned int failure_count = 0;

static testcase_t *create_testcase(const char *name, test_function_t function) {
  testcase_t *result = malloc(sizeof(testcase_t));
  result->name = name;
  result->function = function;
  result->next = NULL;
  return result;
}

void add_testcase(const char *name, test_function_t function) {
  struct testcase_t *testcase;
  struct testcase_t *prev;

  testcase = create_testcase(name, function);
  if (first_testcase == NULL) {
    first_testcase = testcase;
  } else {
    prev = first_testcase;
    while (prev->next != NULL) {
      prev = prev->next;
    }
    prev->next = testcase;
  }
}

static void run_testcase(testcase_t *testcase) {
  unsigned int start_failure_count;
  clock_t start_time, end_time;
  double elapsed_time;

  start_time = clock();
  printf("=== RUN   %s\n", testcase->name);
  start_failure_count = assertion_failed_count;
  run_count++;
  (*testcase->function)();
  end_time = clock();
  elapsed_time = (end_time - start_time) / (double)CLOCKS_PER_SEC;
  if (assertion_failed_count > start_failure_count) {
    failure_count++;
    printf("--- FAIL: %s   (%.3fs)\n", testcase->name, elapsed_time);
  } else {
    printf("--- PASS: %s   (%.3fs)\n", testcase->name, elapsed_time);
  }
}

void run_tests(void) {
  testcase_t *testcase = first_testcase;
  while (testcase != NULL) {
    run_testcase(testcase);
    testcase = testcase->next;
  }
}

int get_failure_count(void) { return failure_count; }

void print_summary(void) {
  printf("\n");
  if (failure_count == 0) {
    if (run_count == 1) {
      printf("OK (%u test)\n", run_count);
    } else {
      printf("OK (%u tests)\n", run_count);
    }
  } else {
    printf("FAILURES!!!\n");
    printf("Tests run: %u,  Failures: %u\n", run_count, failure_count);
  }
}

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line) {
  if (condition) {
    return;
  }

  assertion_failed_count++;
  printf("    %s:%u: %s\n", file, line, message);
}
