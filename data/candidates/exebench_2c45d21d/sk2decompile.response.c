char last_char(char *s) {
  char *p = s;
  char c;
  if (s == NULL || *s == '\0') return '\0';
  while (*p != '\0') p++;
  p--;
  c = *p;
  *p = '\0';
  return c;
}