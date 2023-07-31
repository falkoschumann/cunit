/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include <assert.h>

#include "../src/cunit.h"
#include "failing_suite.h"
#include "successful_suite.h"

int main(void) {
  int failure_count = 0;

  add_successful_suite();
  run_tests();
  failure_count += get_failure_count();
  clear_tests();

  run_tests();
  failure_count += get_failure_count();
  clear_tests();

  failure_count -= get_expected_failure_count();
  return failure_count;
}
