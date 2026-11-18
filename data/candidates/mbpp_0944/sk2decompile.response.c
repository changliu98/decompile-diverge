int _isdigit(const char *str) {
  int i;
  for (i = 0; str[i]; i++) {
    if (isdigit(str[i])) {
      return i;
    }
  }
  return -1;
}