/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include <assert.h>

#include "../src/cunit.h"

static int expected_failure_count = 0;

void test_condition_successfully(void) {
  ASSERT_TRUE(1 == 1);
  ASSERT_FALSE(1 == 2);
}

void test_equals_successfully(void) {
  ASSERT_LONG_EQUALS(1, 1);
  ASSERT_LONG_NOT_EQUALS(1, 2);
  ASSERT_DOUBLE_EQUALS(1.0, 1.05, 0.1);
  ASSERT_DOUBLE_NOT_EQUALS(1.0, 1.1, 0.1);
  ASSERT_STRING_EQUALS("foobar", "foobar");
  ASSERT_STRING_NOT_EQUALS("foo", "bar");
}

void test_pointer_successfully(void) {
  char *pointer = "foo";
  char *same_pointer = pointer;
  char *other_pointer = "bar";
  char *null_pointer = 0;

  ASSERT_NULL(null_pointer);
  ASSERT_NOT_NULL(pointer);
  ASSERT_SAME(pointer, same_pointer);
  ASSERT_NOT_SAME(pointer, other_pointer);
}

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

int main(void) {
  int failure_count = 0;
  testsuite_t *suite;

  suite = add_testsuite("Successful tests");
  add_testcase(suite, "Test condition successfully",
               test_condition_successfully);
  add_testcase(suite, "Test equals successfully", test_equals_successfully);
  add_testcase(suite, "Test pointer successfully", test_pointer_successfully);
  run_tests();
  failure_count += get_failure_count();
  clear_tests();

  suite = add_testsuite("Failing tests");
  add_testcase(suite, "Test condition failed", test_condition_failed);
  add_testcase(suite, "Test equals failed", test_equals_failed);
  add_testcase(suite, "Test pointer failed", test_pointer_failed);
  run_tests();
  failure_count += get_failure_count();
  clear_tests();

  failure_count -= expected_failure_count;
  return failure_count;
}
