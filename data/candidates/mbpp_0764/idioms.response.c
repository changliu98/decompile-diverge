int func0(char *str)
{
  int number_ctr = 0;
  int i;
  for (i = 0; i < strlen(str); i++)
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      number_ctr++;
    }
  }
  return number_ctr;
}