char *char_replace(char *str, char find, char replace) {
  char *p, *q;
  if (str == NULL || *str == '\0') return str;
  p = str;
  while ((q = strchr(p, find)) != NULL) *q++ = replace;
  return str;
}