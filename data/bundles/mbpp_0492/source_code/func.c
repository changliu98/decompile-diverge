

#include <assert.h>



int func0(int item_list[], int size, int item) {
  int first = 0;
  int last = size - 1;
  int found = 0;
  while (first <= last && !found) {
    int mid = (first + last) / 2;
    if (item_list[mid] == item) {
      found = 1;
    } else {
      if (item < item_list[mid]) {
        last = mid - 1;
      } else {
        first = mid + 1;
      }
    }
  }
  return found;
}
