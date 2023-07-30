/*
 * CUnit
 *
 * Copyright (c) 2023 by Falko Schumann <falko.schumann@muspellheim.de>
 * All rights reserved
 * Released under the terms of the MIT License.
 */

#ifndef ASSERTS_H
#define ASSERTS_H

#define ASSERT_TRUE(value)                                            \
  {                                                                   \
    assert_implementation((value), ("expected: true but was: false"), \
                          __FILE__, __LINE__);                        \
  }

/* Prints a summary of the test suite.
 *
 * Returns the number of failed tests or 0 if all tests pass.
 */
int print_summary(void);

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line);

#endif /* ASSERTS_H */
