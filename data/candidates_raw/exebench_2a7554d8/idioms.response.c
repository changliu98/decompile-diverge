int strreplace(char *str, char what, char to)
{
  char *p = strchr(str, what);
  while (p != ((void *)0)) {
    *p = to;
    p = strchr(p + 1, what);
  }
  return 0;
}