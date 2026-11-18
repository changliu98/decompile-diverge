void func0(char *str, char *result)
{
  int i = 0; int j = 0;
  while (str[i])
  {
    if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISspace))
    {
      result[j++] = str[i];
    }
    i++;
  }
  result[j] = '\0';
}