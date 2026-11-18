void sort(char *str)
{
  int i; int j;
  char tmp;
  for (j = 1; j < 10; j++)
  {
    for (i = 0; ; i++)
    {
      int flag = 0;
      if (i < 10 - j)
      {
        if (str[i])
        {
          flag = 1;
        }
      }
      if (!flag)
      {
        break;
      }
      if (str[i] > str[i + 1])
      {
        tmp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = tmp;
      }
    }
  }
}