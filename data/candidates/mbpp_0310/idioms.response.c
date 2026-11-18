char *func0(char *str, char *result)
{
  int i; int j = 0;
  for (i = 0; i < strlen(str); i++)
    if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISspace))
      result[j++] = str[i];
  result[j] = '\0';
  return (result);
}