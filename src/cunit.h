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

void add_testcase(const char *name, test_function_t function);

void run_tests(void);

int get_failure_count(void);

void print_summary(void);

#define ASSERT_TRUE(value)                                            \
  {                                                                   \
    assert_implementation((value), ("expected: true but was: false"), \
                          __FILE__, __LINE__);                        \
  }

#define ASSERT_FALSE(value)                                            \
  {                                                                    \
    assert_implementation(!(value), ("expected: false but was: true"), \
                          __FILE__, __LINE__);                         \
  }

#define ASSERT_EQUALS(expected, actual)                                  \
  {                                                                      \
    assert_implementation((expected == actual),                          \
                          ("expected: " #expected " but was: " #actual), \
                          __FILE__, __LINE__);                           \
  }

#define ASSERT_NOT_EQUALS(expected, actual)                              \
  {                                                                      \
    assert_implementation((expected != actual),                          \
                          ("expected: " #expected " but was: " #actual), \
                          __FILE__, __LINE__);                           \
  }

#define ASSERT_DOUBLE_EQUALS(expected, actual, delta)                    \
  {                                                                      \
    assert_implementation((fabs(expected - actual) < delta),             \
                          ("expected: " #expected " but was: " #actual), \
                          __FILE__, __LINE__);                           \
  }

#define ASSERT_DOUBLE_NOT_EQUALS(expected, actual, delta)                \
  {                                                                      \
    assert_implementation((fabs(expected - actual) >= delta),            \
                          ("expected: " #expected " but was: " #actual), \
                          __FILE__, __LINE__);                           \
  }

#define ASSERT_STRING_EQUALS(expected, actual)                           \
  {                                                                      \
    assert_implementation((strcmp(expected, actual) == 0),               \
                          ("expected: " #expected " but was: " #actual), \
                          __FILE__, __LINE__);                           \
  }

#define ASSERT_STRING_NOT_EQUALS(expected, actual)                       \
  {                                                                      \
    assert_implementation((strcmp(expected, actual) != 0),               \
                          ("expected: " #expected " but was: " #actual), \
                          __FILE__, __LINE__);                           \
  }

#define ASSERT_NULL(value)                                                 \
  {                                                                        \
    assert_implementation((NULL == (const void *)(value)),                 \
                          ("expected: null pointer"), __FILE__, __LINE__); \
  }

#define ASSERT_NOT_NULL(value)                                                 \
  {                                                                            \
    assert_implementation((NULL != (const void *)(value)),                     \
                          ("expected: non null pointer"), __FILE__, __LINE__); \
  }

#define ASSERT_SAME(expected, actual)                         \
  {                                                           \
    assert_implementation(                                    \
        ((const void *)(expected) == (const void *)(actual)), \
        ("expected: same pointer"), __FILE__, __LINE__);      \
  }

#define ASSERT_NOT_SAME(expected, actual)                     \
  {                                                           \
    assert_implementation(                                    \
        ((const void *)(expected) != (const void *)(actual)), \
        ("expected: not same pointer"), __FILE__, __LINE__);  \
  }

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line);

#endif /* ASSERTS_H */
