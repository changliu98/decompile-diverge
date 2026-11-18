#include <assert.h>

#include <stdbool.h>



bool func0(int arraynums[], int length) {
  bool found_duplicate = false;
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (arraynums[i] == arraynums[j]) {
        found_duplicate = true;
        break;
      }
    }
    if (found_duplicate) {
      break;
    }
  }
  return found_duplicate;
}
