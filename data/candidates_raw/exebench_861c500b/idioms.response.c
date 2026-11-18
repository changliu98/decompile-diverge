char *strndup(char *s, char *d)
{
  int i = 0; int j = 0;
  while (s[i]) {
    if (s[i] == '\b') {
      if (--j < 0) j = 0;
    }
    else d[j++] = s[i];
    i++;
  }
  d[j] = '\0';
  return d;
}