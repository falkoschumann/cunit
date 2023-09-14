/*
 * Copyright (c) 2023 by BitCtrl Systems GmbH <info@bitctrl.de>
 * All rights reserved
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/cunit.h"

void test_example(void) {
  int a, b, c;

  a = 1;
  b = 2;

  c = a + b;

  ASSERT_LONG_EQUALS(3, c);
}

int main(int argc, char *argv[]) {
  int i, runs;
  clock_t t;

  t = clock();

  if (argc == 2) {
    runs = atoi(argv[1]);
  } else {
    runs = 10;
  }

  for (i = 0; i < runs; i++) {
    testsuite_t *suite;

    suite = add_testsuite("Example suite", NULL, NULL);
    add_testcase(suite, "Example test", test_example);
    run_tests();
  }

  t = clock() - t;
  printf("Took %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
}
