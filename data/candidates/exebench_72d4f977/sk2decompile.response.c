int endGB(char *line, int *err) {
  *err = 0;
  int ret = 1;
  if (strstr(line, "//") != NULL) {
    ret = 0;
  }
  if (strstr(line, "LOCUS") == line) {
    ret = 1;
  }
  return ret;
}