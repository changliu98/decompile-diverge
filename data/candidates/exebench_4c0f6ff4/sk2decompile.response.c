int endGCGdata(char *line, int *err) {
  *err = 0;
  if (*line == '>')
    return 1;
  else
    return 0;
}