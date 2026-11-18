int func0(const char *test_str) {
  int cnt = 0;
  int res = 0;
  int length = strlen(test_str);
  for (int idx = 0; idx < length; idx++) {
    if (isupper(test_str[idx])) {
      cnt++;
    } else {
      if (cnt > res) {
        res = cnt;
      }
      cnt = 0;
    }
  }
  if (isupper(test_str[length - 1])) {
    if (cnt > res) {
      res = cnt;
    }
  }
  return res;
}