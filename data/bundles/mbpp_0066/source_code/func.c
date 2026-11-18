

#include <assert.h>



int func0(int* list, int list_size) {
  int pos_count = 0;
  for (int i = 0; i < list_size; i++) {
    if (list[i] >= 0) {
      pos_count++;
    }
  }
  return pos_count;
}
