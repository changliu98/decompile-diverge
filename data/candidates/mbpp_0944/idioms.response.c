int func0(char *str)
{
  int i;
  for (i = 0; str[i]; i++)
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISxdigit))
      return i;
  return -1;
}