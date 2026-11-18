char *func0(char *str)
{
  int i; int j = 0;
  for (i = 0; i < strlen(str); i++)
  {
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISalnum))
    {
      result[j++] = str[i];
    }
  }
  result[j] = '\0';
  return result;
}