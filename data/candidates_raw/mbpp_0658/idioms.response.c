int most_common(int *list, int length)
{
  int max_val = 0;
  int most_common = list[0];
  int i; int j;
  int occu;
  for (i = 0; i < length; i++)
  {
    occu = 0;
    for (j = 0; j < length; j++)
    {
      if (list[j] == list[i])
      {
        occu++;
      }
    }
    if (occu > max_val)
    {
      max_val = occu;
      most_common = list[i];
    }
  }
  return most_common;
}