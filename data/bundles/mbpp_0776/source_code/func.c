

#include <stdio.h>

#include <assert.h>

#include <string.h>



int func0(const char *test_str) {
  int res = 0;
  const char *vow_list = "aeiou";
  int len = strlen(test_str);
  for (int idx = 1; idx < len - 1; idx++) {
    if (strchr(vow_list, test_str[idx]) == NULL &&
        (strchr(vow_list, test_str[idx - 1]) != NULL ||
         strchr(vow_list, test_str[idx + 1]) != NULL)) {
      res += 1;
    }
  }
  if (strchr(vow_list, test_str[0]) == NULL &&
      strchr(vow_list, test_str[1]) != NULL) {
    res += 1;
  }
  if (strchr(vow_list, test_str[len - 1]) == NULL &&
      strchr(vow_list, test_str[len - 2]) != NULL) {
    res += 1;
  }
  return res;
}
