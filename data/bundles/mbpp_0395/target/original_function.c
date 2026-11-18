char func0(char* str1) {
  int ctr[256] = {0};
  char char_order[256];
  int idx = 0;
  int length = strlen(str1);
  for (int i = 0; i < length; i++) {
    char c = str1[i];
    if (ctr[c] == 0) {
      char_order[idx++] = c;
    }
    ctr[c]++;
  }
  for (int i = 0; i < idx; i++) {
    char c = char_order[i];
    if (ctr[c] == 1) {
      return c;
    }
  }
  return '\0';
}