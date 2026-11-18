char* func0(const char* s) {
  static char res[1000];
  int l = strlen(s);
  int pos = 0;
  for (int i = 1; i <= l; i++) {
    pos += sprintf(&res[pos], "%d", i);
  }
  for (int i = l - 1; i > 0; i--) {
    pos += sprintf(&res[pos], "%d", i);
  }
  res[pos] = '\0';
  return res;
}