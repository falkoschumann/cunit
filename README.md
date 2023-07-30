[![Build](https://github.com/falkoschumann/cunit/actions/workflows/build.yml/badge.svg)](https://github.com/falkoschumann/cunit/actions/workflows/build.yml)

# CUnit

A simple unit test framework for the C language.

## Installation

Build project with `make` and copy files from then `build/dist` directory.

## Usage

```c
#include "cunit.h"

void test_example(void) {
  int a, b, c;

  a = 1;
  b = 2;

  c = a + b;

  ASSERT_EQUALS(3, c);
}

int main(void) {
  testsuite_t *suite;

  suite = add_testsuite("Example suite");
  add_testcase(suite, "Example test", test_example);
  run_tests();
  return get_failure_count();
}
```

## Contributing

Build with `make`. Other useful tasks:

-   `make clean` - Remove build artifacts.
-   `make format` - Format the source code according to the code style.

## License

Released under the terms of the MIT License.
