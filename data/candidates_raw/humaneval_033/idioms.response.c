void sort(int *in, int size, int *out)
{
  int *third = (int *)malloc((size / 3 + 1) * sizeof(int));
  int third_size = 0;
  int i; int j; int min_idx; int temp;
  for (i = 0; i * 3 < size; i++)
  {
    third[i] = in[i * 3];
    third_size++;
  }
  for (i = 0; i < third_size - 1; i++)
  {
    min_idx = i;
    for (j = i + 1; j < third_size; j++)
    {
      if (third[j] < third[min_idx])
        min_idx = j;
    }
    if (min_idx != i)
    {
      temp = third[i];
      third[i] = third[min_idx];
      third[min_idx] = temp;
    }
  }
  for (i = 0; i < size; i++)
  {
    if (i % 3 == 0)
      out[i] = third[i / 3];
    else
      out[i] = in[i];
  }
  free(third);
}