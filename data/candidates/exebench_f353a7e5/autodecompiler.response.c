void strip(char *s) {
  int i, j, k, l;
  char *c;

  if (s == NULL)
    return;

  c = s;
  for (i = 1; ; i++) {
    if (s[i] == '\0')
      break;
    for (j = 0; j < i; j++)
      if (c[j] == s[i]) {
        s[i] = -1;
        break;
      }
  }

  k = 0;
  l = 0;
  for (i = 1; ; i++) {
    if (s[i] == '\0')
      break;
    if (s[i] == -1) {
      k = i;
      while (s[i] == -1)
        i++;
      l = i;
      break;
    }
  }

  if (k == 0)
    return;

  while (1) {
    if (s[l] == '\0')
      break;
    if (s[l] == -1) {
      l++;
      continue;
    }
    s[k++] = s[l];
    s[l++] = -1;
  }
  s[k] = '\0';
}