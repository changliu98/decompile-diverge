static int parse_width(const char *fmt, int *len) {
  int i, width = 0;
  for (i = 0; fmt[i] && fmt[i] >= '0' && fmt[i] <= '9'; i++)
    width = width * 10 + (fmt[i] - '0');
  *len = i;
  return width;
}