int ExtractRnick(char *rnick, char *s) {
  char *p = s;
  int i = 0;
  if (*p == ':') p++;
  while (*p != '!' && *p != '\0') {
    rnick[i] = *p;
    i++;
    p++;
  }
  rnick[i] = '\0';
  if (rnick[0] < '0') return 0;
  return 1;
}