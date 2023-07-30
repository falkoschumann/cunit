/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include <assert.h>

#include "../src/asserts.h"

void run_successful(void) {
  unsigned int expected_failures = 0;
  unsigned int failure_count;

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

  failure_count = print_summary();
  assert(failure_count == expected_failures);
}

void run_failing(void) {
  unsigned int expected_failures = 0;
  unsigned int failure_count;

  char *pointer = "foo";
  char *same_pointer = pointer;
  char *other_pointer = "bar";
  char *null_pointer = 0;

  ASSERT_TRUE(1 == 2);
  expected_failures++;

  ASSERT_FALSE(1 == 1);
  expected_failures++;

  ASSERT_EQUALS(1, 2);
  expected_failures++;

  ASSERT_NOT_EQUALS(1, 1);
  expected_failures++;

  ASSERT_DOUBLE_EQUALS(1.0, 1.1, 0.1);
  expected_failures++;

  ASSERT_DOUBLE_NOT_EQUALS(1.0, 1.05, 0.1);
  expected_failures++;

  ASSERT_STRING_EQUALS("foo", "bar");
  expected_failures++;

  ASSERT_STRING_NOT_EQUALS("foobar", "foobar");
  expected_failures++;

  ASSERT_NULL(pointer);
  expected_failures++;

  ASSERT_NOT_NULL(null_pointer);
  expected_failures++;

  ASSERT_SAME(pointer, other_pointer);
  expected_failures++;

  ASSERT_NOT_SAME(pointer, same_pointer);
  expected_failures++;

  failure_count = print_summary();
  assert(failure_count == expected_failures);
}

int main(void) {
  run_successful();
  run_failing();
  return 0;
}
