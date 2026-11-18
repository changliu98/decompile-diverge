double func0(double *array, int length)
{
  if (length < 2)
  {
    return -9999999;
  }
  int i; int j;
  int count = 0;
  for (i = 0; i < length; i++)
  {
    for (j = i + 1; j < length; j++)
    {
      if (array[j] == array[i])
      {
        count++;
        break;
      }
    }
  }
  if (length == 2 && count == 1)
  {
    return -9999999;
  }
  double *uniq_items = (double *)malloc(length * sizeof(double));
  int uniq_length = 0;
  for (i = 0; i < length; i++)
  {
    int found = 0;
    for (j = 0; j < uniq_length; j++)
    {
      if (uniq_items[j] == array[i])
      {
        found = 1;
        break;
      }
    }
    if (found == 0)
    {
      uniq_items[uniq_length++] = array[i];
    }
  }
  int k; int l;
  double temp;
  for (k = 0; k < uniq_length; k++)
  {
    for (l = k + 1; l < uniq_length; l++)
    {
      if (uniq_items[k] > uniq_items[l])
      {
        temp = uniq_items[k];
        uniq_items[k] = uniq_items[l];
        uniq_items[l] = temp;
      }
    }
  }
  double second_min = uniq_items[1];
  free(uniq_items);
  return second_min;
}