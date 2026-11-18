char *strrev(char *str)
{
  int i; int j;
  int nletter = 0;
  int length = strlen(str);
  for (i = 0; i < length; i++)
  {
    if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISalnum))
    {
      nletter++;
    }
    else if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISlower))
    {
      if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISupper))
      {
        str[i] = tolower(str[i]);
      }
    }
    else
    {
      str[i] = toupper(str[i]);
    }
  }
  if (nletter == length)
  {
    for (j = 0; j < length / 2; j++)
    {
      char temp = str[j];
      str[j] = str[length - j - 1];
      str[length - j - 1] = temp;
    }
  }
  return str;
}