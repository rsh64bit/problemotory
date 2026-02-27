#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void converging_sum(uint32_t *sample, uint32_t len, uint32_t sum) {

  uint32_t *s = sample, n = len, *f = sample + n - 1;

  for (uint32_t i = 0; i < n; ++i) {
    if (*s + *f > sum) {
      f = f - 1;
    } else if (*s + *f < sum)
      s += 1;
  }
  printf("sum part of %d {%d %d}\n", sum, *s, *f);
}

int main() {
  /*make sure it is sorted*/
  uint32_t sum = 10;
  // uint32_t arr[] = {1, 2 ,4, 6, 8, 11, 15};
  uint32_t arr[] = {1, 2, 4, 6, 9, 11, 15};
  converging_sum(arr, sizeof(arr) / sizeof(arr[0]), sum);
  return 0;
}
