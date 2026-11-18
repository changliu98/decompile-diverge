void endStrider(char *line, int *end) {
  *end = 0;
  if (strstr(line, "//") != NULL) {
    *end = 1;
  }
}