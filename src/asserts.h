#ifndef ASSERTS_H
#define ASSERTS_H

#define ASSERT_TRUE(value)                                            \
  {                                                                   \
    assert_implementation((value), ("expected: true but was: false"), \
                          __FILE__, __LINE__);                        \
  }

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line);

#endif /* ASSERTS_H */
