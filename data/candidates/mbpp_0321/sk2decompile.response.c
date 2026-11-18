char *func0(char *s) {
  static char buf[1000];
  int len = strlen(s);
  int i, j = 0;
  for (i = 1; i <= len; i++) j += sprintf(buf + j, "%d", i);
  for (i = len - 1; i >= 1; i--) j += sprintf(buf + j, "%d", i);
  buf[j] = 0;
  return buf;
}