#include "../src/asserts.h"

static unsigned int expected_failures = 0;
static unsigned int failure_count;

void run_successful(void) { ASSERT_TRUE(1 == 1); }

void run_failing(void) {
  ASSERT_TRUE(1 == 2);
  expected_failures++;
}

int main(void) {
  int ok;
  run_successful();
  run_failing();

  failure_count = print_summary();
  ok = failure_count - expected_failures;
  return ok;
}
