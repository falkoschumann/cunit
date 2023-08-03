/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#include "successful_suite.h"

#include "../src/cunit.h"

static void test_bool(void) {
  ASSERT_TRUE(1 == 1);
  ASSERT_FALSE(1 == 2);
}

static void test_number(void) {
  ASSERT_LONG_EQUALS(1, 1);
  ASSERT_LONG_NOT_EQUALS(1, 2);
  ASSERT_DOUBLE_EQUALS(1.0, 1.05, 0.1);
  ASSERT_DOUBLE_NOT_EQUALS(1.0, 1.1, 0.1);
}

static void test_string(void) {
  ASSERT_STRING_EQUALS("foobar", "foobar");
  ASSERT_STRING_NOT_EQUALS("foo", "bar");
}

static void test_pointer(void) {
  char *pointer = "foo";
  char *same_pointer = pointer;
  char *other_pointer = "bar";
  char *null_pointer = 0;

  ASSERT_NULL(null_pointer);
  ASSERT_NOT_NULL(pointer);
  ASSERT_SAME(pointer, same_pointer);
  ASSERT_NOT_SAME(pointer, other_pointer);
}

void add_successful_suite(void) {
  testsuite_t *suite;

  suite = add_testsuite("Successful tests", NULL, NULL);
  add_testcase(suite, "Bool", test_bool);
  add_testcase(suite, "Number", test_number);
  add_testcase(suite, "String", test_string);
  add_testcase(suite, "Pointer", test_pointer);
}
