void plural(char *s) {
  while (*s)
    s++;
  s--;
  *s = 's';
}