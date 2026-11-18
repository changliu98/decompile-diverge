int tounsigned(char *line, int *err, int pos) {
  char c;
  while (1) {
    c = line[pos];
    if (c == ' ' || c == '\t' || c > 13)
      c = 0;
    if (!c)
      break;
    pos++;
  }
  if (line[pos] == 0)
    *err = -3;
  if (line[pos] == '-')
    *err = -2;
  return pos;
}