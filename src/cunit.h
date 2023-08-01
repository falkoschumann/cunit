/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#ifndef ASSERTS_H
#define ASSERTS_H

#include <math.h>
#include <string.h>

typedef void (*test_function_t)(void);
typedef void (*setup_function_t)(void);
typedef void (*teardown_function_t)(void);

typedef struct testcase_t {
  const char *name;
  test_function_t function;
  struct testcase_t *next;
} testcase_t;

typedef struct testsuite_t {
  const char *name;
  struct testcase_t *first_testcase;
  setup_function_t setup;
  teardown_function_t teardown;
  struct testsuite_t *next;
} testsuite_t;

testsuite_t *add_testsuite(const char *name, setup_function_t setup,
                           teardown_function_t teardown);

testcase_t *add_testcase(testsuite_t *testsuite, const char *name,
                         test_function_t function);

int run_tests(void);

#define ASSERT_IMPLEMENTATION(condition, message, expected, actual) \
  {                                                                 \
    if (!condition) {                                               \
      fail(__FILE__, __LINE__, message, expected, actual);          \
    }                                                               \
  }

#define ASSERT_TRUE(value)                                                  \
  {                                                                         \
    ASSERT_IMPLEMENTATION((value), "expected: <true> but was: <%d>", value, \
                          NULL);                                            \
  }

#define ASSERT_FALSE(value)                                                   \
  {                                                                           \
    ASSERT_IMPLEMENTATION(!(value), "expected: <false> but was: <%d>", value, \
                          NULL);                                              \
  }

#define ASSERT_LONG_EQUALS(expected, actual)                                 \
  {                                                                          \
    ASSERT_IMPLEMENTATION((expected == actual),                              \
                          "expected: <%d> but was: <%d>", expected, actual); \
  }

#define ASSERT_LONG_NOT_EQUALS(expected, actual)                              \
  {                                                                           \
    ASSERT_IMPLEMENTATION((expected != actual),                               \
                          "expected: not equal but was: <%d>", actual, NULL); \
  }

#define ASSERT_DOUBLE_EQUALS(expected, actual, delta)                        \
  {                                                                          \
    ASSERT_IMPLEMENTATION((fabs(expected - actual) <= delta),                \
                          "expected: <%f> but was: <%f>", expected, actual); \
  }

#define ASSERT_DOUBLE_NOT_EQUALS(expected, actual, delta)                     \
  {                                                                           \
    ASSERT_IMPLEMENTATION((fabs(expected - actual) > delta),                  \
                          "expected: not equal but was: <%f>", actual, NULL); \
  }

#define ASSERT_STRING_EQUALS(expected, actual)                               \
  {                                                                          \
    ASSERT_IMPLEMENTATION((strcmp(expected, actual) == 0),                   \
                          "expected: <%s> but was: <%s>", expected, actual); \
  }

#define ASSERT_STRING_NOT_EQUALS(expected, actual)                            \
  {                                                                           \
    ASSERT_IMPLEMENTATION((strcmp(expected, actual) != 0),                    \
                          "expected: not equal but was: <%s>", actual, NULL); \
  }

#define ASSERT_NULL(value)                                                \
  {                                                                       \
    ASSERT_IMPLEMENTATION((NULL == (const void *)(value)),                \
                          "expected: <null> but was: <%p>", value, NULL); \
  }

#define ASSERT_NOT_NULL(value)                                 \
  {                                                            \
    ASSERT_IMPLEMENTATION((NULL != (const void *)(value)),     \
                          "expected: not <null>", NULL, NULL); \
  }

#define ASSERT_SAME(expected, actual)                         \
  {                                                           \
    ASSERT_IMPLEMENTATION(                                    \
        ((const void *)(expected) == (const void *)(actual)), \
        "expected: <%p> but was: <%p>", expected, actual);    \
  }

#define ASSERT_NOT_SAME(expected, actual)                     \
  {                                                           \
    ASSERT_IMPLEMENTATION(                                    \
        ((const void *)(expected) != (const void *)(actual)), \
        "expected: not same but was: <%p>", actual, NULL);    \
  }

void fail(const char *file, unsigned int line, const char *message, ...);

#endif /* ASSERTS_H */
