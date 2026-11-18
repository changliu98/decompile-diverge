

#include <assert.h>



int func0(int x, int y, int z) {
  int result[3] = {x, y, z};
  int unique_values = 0;
  int counts[3] = {0, 0, 0};
  for (int i = 0; i < 3; i++) {
    int found = 0;
    for (int j = 0; j < i; j++) {
      if (result[j] == result[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      unique_values++;
    }
  }
  if (unique_values == 3) {
    return 0;
  } else {
    return (4 - unique_values);
  }
}
