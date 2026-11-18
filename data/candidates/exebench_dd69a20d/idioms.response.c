void remove_all_chars(char *s, char c)
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