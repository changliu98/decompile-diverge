char *func0(char *str)
{
  int hasZero = 0;
  int hasOne = 0;
  int hasOther = 0;
  int i = 0;
  for (i = 0; i < strlen(str); i++)
  {
    if (str[i] == '0')
    {
      hasZero = 1;
    }
    else if (str[i] == '1')
    {
      hasOne = 1;
    }
    else
    {
      hasOther = 1;
      break;
    }
  }
  if ((hasZero || hasOne) && !hasOther)
  {
    return "binary";
  }
  else
  {
    return "not binary";
  }
}