/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "cunit.h"

#include <stdio.h>
#include <time.h>

static unsigned int assertion_failed_count = 0;
static unsigned int run_count = 0;
static unsigned int failure_count = 0;

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line) {
  if (condition) {
    return;
  }

  assertion_failed_count++;
  printf("    %s:%u: %s\n", file, line, message);
}

void run_testcase(testcase_t testcase) {
  unsigned int start_failure_count;
  clock_t start_time, end_time;
  double elapsed_time;

  start_time = clock();
  printf("=== RUN   %s\n", testcase.name);
  start_failure_count = assertion_failed_count;
  run_count++;
  (*testcase.function)();
  end_time = clock();
  elapsed_time = (end_time - start_time) / (double)CLOCKS_PER_SEC;
  if (assertion_failed_count > start_failure_count) {
    failure_count++;
    printf("--- FAIL: %s   (%.3fs)\n", testcase.name, elapsed_time);
  } else {
    printf("--- PASS: %s   (%.3fs)\n", testcase.name, elapsed_time);
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
