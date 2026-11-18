char firstNonRepeatingChar(char *str) {
  char chars[256];
  int counts[256];
  char *s = str;
  int i, len, count;
  char c;
  memset(counts, 0, sizeof(counts));
  count = 0;
  len = strlen(s);
  for (i = 0; i < len; i++) {
    c = s[i];
    if (counts[c] == 0) {
      chars[count++] = c;
    }
    counts[c]++;
  }
  for (i = 0; i < count; i++) {
    if (counts[chars[i]] == 1) {
      return chars[i];
    }
  }
  return 0;
}