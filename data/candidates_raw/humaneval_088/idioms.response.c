void sort(int *in_array, int in_size, int **out_array, int *out_size)
{
  int i; int j; int temp; int temp2; int shouldSortAscending;
  *out_size = in_size;
  if (in_size == 0)
  {
    *out_array = ((void *)0);
    return;
  }
  *out_array = (int *)malloc(in_size * sizeof(int));
  if (*out_array == ((void *)0))
    exit(1);
  for (i = 0; i < in_size; i++)
    (*out_array)[i] = in_array[i];
  if ((in_array[in_size - 1] + in_array[0]) % 2 == 1)
    shouldSortAscending = 1;
  else
    shouldSortAscending = 0;
  for (i = 0; i < in_size - 1; i++)
  {
    for (j = i + 1; j < in_size; j++)
    {
      if (shouldSortAscending)
      {
        if ((*out_array)[i] > (*out_array)[j])
        {
          temp = (*out_array)[i];
          (*out_array)[i] = (*out_array)[j];
          (*out_array)[j] = temp;
        }
      }
      else
      {
        if ((*out_array)[i] < (*out_array)[j])
        {
          temp2 = (*out_array)[i];
          (*out_array)[i] = (*out_array)[j];
          (*out_array)[j] = temp2;
        }
      }
    }
  }
}