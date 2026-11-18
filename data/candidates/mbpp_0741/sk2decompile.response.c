bool _is_all_same(char *str) {
  int len = strlen(str);
  for (int i = 1; i < len; i++) {
    if (str[i] != str[0]) {
      return false;
    }
  }
  return true;
}