/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include <assert.h>

#include "../src/cunit.h"

void run_successful(void) {
  char *pointer = "foo";
  char *same_pointer = pointer;
  char *other_pointer = "bar";
  char *null_pointer = 0;

  ASSERT_TRUE(1 == 1);
  ASSERT_FALSE(1 == 2);
  ASSERT_EQUALS(1, 1);
  ASSERT_NOT_EQUALS(1, 2);
  ASSERT_DOUBLE_EQUALS(1.0, 1.05, 0.1);
  ASSERT_DOUBLE_NOT_EQUALS(1.0, 1.1, 0.1);
  ASSERT_STRING_EQUALS("foobar", "foobar");
  ASSERT_STRING_NOT_EQUALS("foo", "bar");
  ASSERT_NULL(null_pointer);
  ASSERT_NOT_NULL(pointer);
  ASSERT_SAME(pointer, same_pointer);
  ASSERT_NOT_SAME(pointer, other_pointer);
}

void run_failing(void) {
  char *pointer = "foo";
  char *same_pointer = pointer;
  char *other_pointer = "bar";
  char *null_pointer = 0;

  ASSERT_TRUE(1 == 2);
  ASSERT_FALSE(1 == 1);
  ASSERT_EQUALS(1, 2);
  ASSERT_NOT_EQUALS(1, 1);
  ASSERT_DOUBLE_EQUALS(1.0, 1.1, 0.1);
  ASSERT_DOUBLE_NOT_EQUALS(1.0, 1.05, 0.1);
  ASSERT_STRING_EQUALS("foo", "bar");
  ASSERT_STRING_NOT_EQUALS("foobar", "foobar");
  ASSERT_NULL(pointer);
  ASSERT_NOT_NULL(null_pointer);
  ASSERT_SAME(pointer, other_pointer);
  ASSERT_NOT_SAME(pointer, same_pointer);
}

int main(void) {
  int ok, expected_failure_count;

  expected_failure_count = 1;
  add_testcase("Successful test case", run_successful);
  add_testcase("Failing test case", run_failing);
  run_tests();
  print_summary();
  ok = get_failure_count() - expected_failure_count;

  return ok;
}
