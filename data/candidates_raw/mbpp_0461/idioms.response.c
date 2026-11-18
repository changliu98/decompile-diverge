int isupper(char *str)
{
  int i = 0;
  int upper_ctr = 0;
  if (strlen(str))
  {
    if (str[i] >= 'A')
    {
      if (str[i] <= 'Z')
      {
        upper_ctr++;
      }
    }
    if (upper_ctr == 0)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
  return 0;
}