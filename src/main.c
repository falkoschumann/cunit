/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "cunit.h"

void test_example(void) {
  int a, b, c;

  a = 1;
  b = 2;

  c = a + b;

  ASSERT_LONG_EQUALS(3, c);
}

int main(void) {
  testsuite_t *suite;

  suite = add_testsuite("Example suite");
  add_testcase(suite, "Example test", test_example);
  return run_tests();
}
