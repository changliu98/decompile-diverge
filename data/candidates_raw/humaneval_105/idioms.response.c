void get_namelist(int *in, int in_size, char ***out, int *out_size)
{
  int i; int j; int k; int temp;
  char *namelist[10] = {
    "1", "2", "3", "4", "5",
    "6", "7", "8", "9", "10"
  };
  int in_array[10];
  int in_size_array;
  char **out_array;
  memcpy(in_array, in, sizeof(in_array));
  for (i = 0; i < in_size - 1; i++)
  {
    for (j = 0; j < in_size - i - 1; j++)
    {
      if (in_array[j] > in_array[j + 1])
      {
        temp = in_array[j];
        in_array[j] = in_array[j + 1];
        in_array[j + 1] = temp;
      }
    }
  }
  *out_size = 0;
  for (i = in_size - 1; i >= 0; i--)
  {
    if (in_array[i] >= 1 && in_array[i] <= 9)
    {
      (*out_size)++;
    }
  }
  *out = (char **)malloc((*out_size) * sizeof(char *));
  for (i = in_size - 1, j = 0; i >= 0 && j < *out_size; i--)
  {
    if (in_array[i] >= 1 && in_array[i] <= 9)
    {
      (*out)[j++] = namelist[in_array[i]];
    }
  }
}