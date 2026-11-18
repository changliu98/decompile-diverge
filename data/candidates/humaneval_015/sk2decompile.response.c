char *__gmp_seq_str(int n) {
  int i, len = 2;
  char *s, *p;
  for (i = 1; i <= n; i++) len += snprintf(NULL, 0, " %d", i);
  s = malloc(len);
  if (!s) return NULL;
  p = s + sprintf(s, "0");
  for (i = 1; i <= n; i++) p += sprintf(p, " %d", i);
  return s;
}