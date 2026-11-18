static int parse_matrix_header(char *line, int *width, int *height,
                               double *scale, double *offset) {
  double d[4];
  char *start, *end;
  int n;
  end = strchr(line, '\r');
  if (end == NULL) end = strchr(line, '\n');
  if (end) *end = '\0';
  n = 0;
  start = line;
  end = vips_break_token(start, " \t");
  while (end != NULL && n < 4) {
    if (vips_strtod(start, &d[n])) {
      vips_error("matload", "bad number \"%s\"", start);
      return -1;
    }
    n++;
    start = end;
    end = vips_break_token(start, " \t");
  }
  if (n < 4) d[3] = 0.0;
  if (n < 3) d[2] = 1.0;
  if (n < 2) {
    vips_error("matload", "%s", "no width / height");
    return -1;
  }
  if (floor(d[0]) != d[0] || floor(d[1]) != d[1]) {
    vips_error("mask2vips", "%s", "width / height not int");
    return -1;
  }
  *width = d[0];
  *height = d[1];
  if (*width < 1 || *width > 100000 || *height < 1 || *height > 100000) {
    vips_error("mask2vips", "%s", "width / height out of range");
    return -1;
  }
  if (d[2] == 0.0) {
    vips_error("mask2vips", "%s", "zero scale");
    return -1;
  }
  *scale = d[2];
  *offset = d[3];
  return 0;
}