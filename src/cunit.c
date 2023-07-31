/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "cunit.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static testsuite_t *first_testsuite = NULL;

static unsigned int assertion_failed_count = 0;
static unsigned int run_count = 0;
static unsigned int failure_count = 0;

static testsuite_t *create_testsuite(const char *name) {
  testsuite_t *result = malloc(sizeof(testsuite_t));
  if (result == NULL) {
    return NULL;
  }

  result->name = name;
  result->first_testcase = NULL;
  result->next = NULL;
  return result;
}

testsuite_t *add_testsuite(const char *name) {
  struct testsuite_t *testsuite;
  struct testsuite_t *prev;

  testsuite = create_testsuite(name);
  if (testsuite == NULL) {
    return NULL;
  }

  if (first_testsuite == NULL) {
    first_testsuite = testsuite;
  } else {
    prev = first_testsuite;
    while (prev->next != NULL) {
      prev = prev->next;
    }
    prev->next = testsuite;
  }
  return testsuite;
}

static testcase_t *create_testcase(const char *name, test_function_t function) {
  testcase_t *result = malloc(sizeof(testcase_t));
  if (result == NULL) {
    return NULL;
  }

  result->name = name;
  result->function = function;
  result->next = NULL;
  return result;
}

testcase_t *add_testcase(testsuite_t *testsuite, const char *name,
                         test_function_t function) {
  struct testcase_t *testcase;
  struct testcase_t *prev;

  testcase = create_testcase(name, function);
  if (testcase == NULL) {
    return NULL;
  }

  if (testsuite->first_testcase == NULL) {
    testsuite->first_testcase = testcase;
  } else {
    prev = testsuite->first_testcase;
    while (prev->next != NULL) {
      prev = prev->next;
    }
    prev->next = testcase;
  }
  return testcase;
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

static void run_testsuite(testsuite_t *testsuite) {
  unsigned int start_failure_count;
  clock_t start_time, end_time;
  double elapsed_time;
  testcase_t *testcase;

  start_time = clock();
  start_failure_count = assertion_failed_count;
  testcase = testsuite->first_testcase;
  while (testcase != NULL) {
    run_testcase(testcase);
    testcase = testcase->next;
  }
  end_time = clock();
  elapsed_time = (end_time - start_time) / (double)CLOCKS_PER_SEC;
  if (assertion_failed_count > start_failure_count) {
    printf("FAIL    %s   (%.3fs)\n", testsuite->name, elapsed_time);
  } else {
    printf("OK      %s   (%.3fs)\n", testsuite->name, elapsed_time);
  }
}

static void print_summary(double run_time) {
  printf("\n");
  printf("Time: %.3fs\n", run_time);
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

void run_tests(void) {
  testsuite_t *testsuite;
  clock_t start_time, end_time;
  double run_time;

  start_time = clock();
  testsuite = first_testsuite;
  while (testsuite != NULL) {
    run_testsuite(testsuite);
    testsuite = testsuite->next;
  }
  end_time = clock();
  run_time = (end_time - start_time) / (double)CLOCKS_PER_SEC;
  print_summary(run_time);
}

int get_failure_count(void) { return failure_count; }

static void clear_testcase(testcase_t *testcase) {
  testcase_t *current_testcase, *next_testcase;

  if (testcase == NULL) {
    return;
  }

  current_testcase = testcase;
  while (current_testcase != NULL) {
    next_testcase = current_testcase->next;
    free(current_testcase);
    current_testcase = next_testcase;
  }
}

static void clear_testsuite(testsuite_t *testsuite) {
  testsuite_t *current_testsuite, *next_testsuite;

  if (testsuite == NULL) {
    return;
  }

  current_testsuite = testsuite;
  while (current_testsuite != NULL) {
    next_testsuite = current_testsuite->next;
    clear_testcase(current_testsuite->first_testcase);
    free(current_testsuite);
    current_testsuite = next_testsuite;
  }
}

void clear_tests(void) {
  assertion_failed_count = 0;
  run_count = 0;
  failure_count = 0;
  clear_testsuite(first_testsuite);
  first_testsuite = NULL;
}

void fail(const char *file, unsigned int line, const char *message, ...) {
  va_list ap;

  assertion_failed_count++;

  va_start(ap, message);
  printf("    %s:%u: ", file, line);
  vprintf(message, ap);
  printf("\n");
  va_end(ap);
}
