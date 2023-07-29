#include <stdio.h>

#include "asserts.h"

void assert_implementation(int condition, const char *message, const char *file,
                           unsigned int line) {
  if (condition) {
    return;
  }

  printf("%s:%u: %s\n", file, line, message);
}
