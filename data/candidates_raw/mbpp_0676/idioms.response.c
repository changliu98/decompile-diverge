char *get_alnum(char *str)
{
  char *res;
  unsigned long i; unsigned long j;
  unsigned long len = strlen(str);
  res = (char *)malloc(len + 1);
  if (res == ((void *)0))
    return ((void *)0);
  for (j = 0, i = 0; i < len; i++)
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISalnum))
      res[j++] = str[i];
  res[j] = '\0';
  return res;
}