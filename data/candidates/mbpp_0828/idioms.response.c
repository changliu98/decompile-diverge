void func0(char *str, int *alphabets, int *digits, int *special)
{
  int i;
  *special = 0;
  *digits = 0;
  *alphabets = 0;
  for (i = 0; str[i]; i++)
  {
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISalpha))
    {
      (*alphabets)++;
    }
    else if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISdigit))
    {
      (*digits)++;
    }
    else
    {
      (*special)++;
    }
  }
}