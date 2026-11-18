void sort(char *str)
{
  int i = 0;
  for (i = 0; str[i + 1]; i++)
  {
    int temp = str[i + 1];
    int j = i;
    while (1)
    {
      int flag = 0;
      if (str[j] > temp)
      {
        if (j == 0)
        {
          str[j + 1] = str[j];
          break;
        }
        else
        {
          str[j + 1] = str[j];
          j--;
        }
      }
      else
      {
        str[j + 1] = temp;
        break;
      }
    }
  }
}