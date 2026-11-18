char *strlower(char *str)
{
  int i; int j = 0;
  for (i = 0; str[i]; i++)
    if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISlower))
      strlower_result[j++] = str[i];
  strlower_result[j] = '\0';
  return strlower_result;
}