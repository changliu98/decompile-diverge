int count(int *tup, int tup_size, int *lst, int lst_size)
{
  int count = 0;
  int i;
  int j;
  for (i = 0; i < tup_size; i++)
  {
    for (j = 0; j < lst_size; j++)
    {
      if (tup[i] == lst[j])
      {
        count++;
        break;
      }
    }
  }
  return (count);
}