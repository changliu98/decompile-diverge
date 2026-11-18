char *_parse_points(char **points, int n) {
  char **p = points;
  int n_p = n;
  int i;
  char buf[100];
  double x, y;
  strcpy(buf_points, "[");
  for (i = 0; i < n_p; i += 2) {
    x = atof(p[i]);
    y = atof(p[i + 1]);
    snprintf(buf, 100, "(%.2f, %.2f)", x, y);
    strcat(buf_points, buf);
    if (i < n_p - 2) strcat(buf_points, ", ");
  }
  strcat(buf_points, "]");
  return buf_points;
}