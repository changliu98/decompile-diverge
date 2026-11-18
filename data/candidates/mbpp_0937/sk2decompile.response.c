char _max_char(char *str) {
  int count[256];
  char *s = str;
  int i, max, len;
  char c;
  memset(count, 0, sizeof(count));
  max = 0;
  c = 0;
  len = strlen(s);
  for (i = 0; i < len; i++) {
    count[(unsigned char)s[i]]++;
    if (count[(unsigned char)s[i]] > max) {
      max = count[(unsigned char)s[i]];
      c = s[i];
    }
  }
  return c;
}