int *__parse_int_list(char *str, int *count) {
  char *p, *q;
  int n = 0;
  int val;
  p = str;
  while (*p) {
    while (*p && !isdigit(*p) && *p != '-') p++;
    if (!*p) break;
    val = strtol(p, &q, 10);
    if (p != q && *q != ',' && *q != '\0') {
      int_list[n++] = val;
    } else {
      while (*q && *q != ',') q++;
    }
    p = q;
  }
  *count = n;
  return int_list;
}