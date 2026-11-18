void rstrchrip(char *s, char c)
{
  char *r = s;
  char *w = s;
  while (*r) {
    if (*r++ == c)
      continue;
    *w = *r;
    w++;
  }
  *w = '\0';
}