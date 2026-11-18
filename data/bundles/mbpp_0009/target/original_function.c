int func0(const char* str) {
  int n = strlen(str);
  char tmp[2 * n + 1];
  strcpy(tmp, str);
  strcat(tmp, str);
  for (int i = 1; i <= n; i++) {
    int equal = 1;
    for (int j = 0; j < n; j++) {
      if (str[j] != tmp[i + j]) {
        equal = 0;
        break;
      }
    }
    if (equal) {
      return i;
    }
  }
  return n;
}