int substitute(char *data, char from, char to) {
  char *p;

  while ((p = strchr(data, from)) != NULL) {
    *p = to;
    p++;
  }

  return 1;
}