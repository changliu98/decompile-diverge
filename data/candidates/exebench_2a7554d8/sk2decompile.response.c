int replace(char *str, char old, char new) {
  char *p;
  p = strchr(str, old);
  while (p != NULL) {
    *p = new;
    p = strchr(p + 1, old);
  }
  return 0;
}