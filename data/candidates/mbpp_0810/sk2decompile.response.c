char *_create_string(int p, int q, int r, int s) {
  int len = 0;
  if (p > 0) len += p;
  if (q > 0) len += q;
  if (r > 0) len += r;
  if (s > 0) len += s;
  char *str = malloc(len + 1);
  if (str == NULL) {
    perror("Failed to allocate memory");
    exit(1);
  }
  int i = 0;
  for (int j = 0; j < p; j++) {
    str[i++] = 'p';
  }
  for (int j = 0; j < q; j++) {
    str[i++] = 'q';
  }
  for (int j = 0; j < r; j++) {
    str[i++] = 'r';
  }
  for (int j = 0; j < s; j++) {
    str[i++] = 's';
  }
  str[i] = '\0';
  return str;
}