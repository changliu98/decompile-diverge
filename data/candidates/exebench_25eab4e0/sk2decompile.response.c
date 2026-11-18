int substitute(char *str, char old, char new) {
  char *p;
  while ((p = strchr(str, old)) != NULL) {
    *p = new;
    str = p + 1;
  }
  return 1;
}