void func0(char *str) {
  char *p = str;
  char *q = str;
  while (*p) {
    if (strchr("AEIOUaeiou", *p) == NULL) {
      *q++ = *p;
    }
    p++;
  }
  *q = '\0';
}