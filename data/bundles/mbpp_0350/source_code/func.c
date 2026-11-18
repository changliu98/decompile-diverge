

#include <assert.h>

#include <string.h>



int func0(const char* s) {
  int maxOcc = 0;
  int n = strlen(s);
  int arr[26] = {0};
  for (int i = 0; i < n; i++) {
    arr[s[i] - 'a']++;
  }
  for (int i = 0; i < 26; i++) {
    if (arr[i] > maxOcc) {
      maxOcc = arr[i];
    }
  }
  return n - maxOcc;
}
