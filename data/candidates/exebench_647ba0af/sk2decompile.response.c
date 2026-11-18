char *replace_char(char *str, char find, char replace) {
  char *p;
  p = strchr(str, find);
  while (p) {
    *p = replace;
    p = strchr(p + 1, find);
  }
  return str;
}