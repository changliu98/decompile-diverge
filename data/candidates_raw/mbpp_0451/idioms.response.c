char *strtrim(char *str)
{
  int i = 0;
  int j = 0;
  while (str[i])
  {
    if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISspace))
      str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
  return (str);
}