int func0(char *s, char *t) {
  int count = 0;
  char *p;
  while (*s) {
    p = t;
    while (*p) {
      if (*s == *p) {
        count++;
        break;
      }
      p++;
    }
    s++;
  }
  return count;
}