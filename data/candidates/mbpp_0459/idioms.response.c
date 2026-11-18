char *func0(char *str)
{
  char *ret;
  unsigned long len = strlen(str);
  unsigned long i; unsigned long j;
  if((ret = (char *)malloc((len + 1)*sizeof(char))) == ((void *)0))
    return ((void *)0);
  for(j = 0, i = 0; i < len; i++)
    if(((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISupper))
      continue;
    else
      ret[j++] = str[i];
  ret[j] = '\0';
  return ret;
}