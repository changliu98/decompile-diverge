

#include <assert.h>

#include <stdlib.h>



void func0(int *my_list, int n) {
  int max_value = 0;
  for (int i = 0; i < n; i++) {
    if (my_list[i] > max_value) {
      max_value = my_list[i];
    }
  }
  int *buckets = malloc((max_value + 1) * sizeof(int));
  for (int j = 0; j <= max_value; j++) {
    buckets[j] = 0;
  }
  for (int i = 0; i < n; i++) {
    buckets[my_list[i]]++;
  }
  int pos = 0;
  for (int j = 0; j <= max_value; j++) {
    for (int a = 0; a < buckets[j]; a++) {
      my_list[pos] = j;
      pos++;
    }
  }
  free(buckets);
}
