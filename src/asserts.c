/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "asserts.h"

#include <stdio.h>

static unsigned int run_count = 0;
static unsigned int failure_count = 0;

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line) {
  run_count++;
  if (condition) {
    return;
  }

  failure_count++;
  printf("%s:%u: %s\n", file, line, message);
}

int print_summary(void) {
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
  return failure_count;
}
