/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "suite_with_setup_and_teardown.h"

#include "../src/cunit.h"
#include "stdio.h"

void setup(void) { printf("set up - "); }

void teardown(void) { printf(" - tear down\n"); }

void test_nothing(void) { printf("test"); }

void add_suite_with_setup_and_teardown(void) {
  testsuite_t *suite;

  suite = add_testsuite("Suite with setup and teardown", setup, teardown);
  add_testcase(suite, "Test nothing", test_nothing);
}
