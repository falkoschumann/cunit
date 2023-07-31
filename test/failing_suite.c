/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "failing_suite.h"

#include "../src/cunit.h"

static int expected_failure_count = 0;

void test_condition_failed(void) {
  expected_failure_count++;

  ASSERT_TRUE(1 == 2);
  ASSERT_FALSE(1 == 1);
}

void test_equals_failed(void) {
  expected_failure_count++;

  ASSERT_LONG_EQUALS(1, 2);
  ASSERT_LONG_NOT_EQUALS(1, 1);
  ASSERT_DOUBLE_EQUALS(1.0, 1.1, 0.1);
  ASSERT_DOUBLE_NOT_EQUALS(1.0, 1.05, 0.1);
  ASSERT_STRING_EQUALS("foo", "bar");
  ASSERT_STRING_NOT_EQUALS("foobar", "foobar");
}

void test_pointer_failed(void) {
  char *pointer = "foo";
  char *same_pointer = pointer;
  char *other_pointer = "bar";
  char *null_pointer = 0;
  expected_failure_count++;

  ASSERT_NULL(pointer);
  ASSERT_NOT_NULL(null_pointer);
  ASSERT_SAME(pointer, other_pointer);
  ASSERT_NOT_SAME(pointer, same_pointer);
}

void add_failing_suite(void) {
  testsuite_t *suite;

  suite = add_testsuite("Failing tests");
  add_testcase(suite, "Test condition failed", test_condition_failed);
  add_testcase(suite, "Test equals failed", test_equals_failed);
  add_testcase(suite, "Test pointer failed", test_pointer_failed);
}

int get_expected_failure_count(void) { return expected_failure_count; }
