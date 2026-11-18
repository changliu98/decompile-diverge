char **func0(int *a, int n, char *sep) {
  char **r = malloc(n * 2 * sizeof(char *));
  int i, j = 0;
  for (i = 0; i < n; i++) {
    asprintf(&r[j++], "%d", a[i]);
    r[j++] = sep;
  }
  return r;
}