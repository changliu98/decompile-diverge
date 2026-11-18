int count_lower(char *str)
{
  int lower_ctr = 0;
  int i = 0;
  for (i = 0; i < strlen(str); i++)
  {
    if (str[i] >= 'a' && str[i] <= 'z')
    {
      lower_ctr++;
    }
  }
  return lower_ctr;
}