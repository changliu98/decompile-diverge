void radixSort(int *array, int size)
{
  int i = 0;
  int max = array[0];
  int placement = 1;
  int *output = ((void *)0);
  int *count = ((void *)0);
  for (i = 1; i < size; i++)
  {
    if (array[i] > max)
    {
      max = array[i];
    }
  }
  output = (int *)malloc(size * sizeof(int));
  count = (int *)malloc(sizeof(int) * 10);
  while (placement <= max)
  {
    for (i = 0; i < 10; i++)
    {
      count[i] = 0;
    }
    for (i = 0; i < size; i++)
    {
      int index = (array[i] / placement) % 10;
      count[index]++;
    }
    for (i = 1; i < 10; i++)
    {
      count[i] += count[i - 1];
    }
    for (i = size - 1; i >= 0; i--)
    {
      int index = (array[i] / placement) % 10;
      output[count[index] - 1] = array[i];
      count[index]--;
    }
    for (i = 0; i < size; i++)
    {
      array[i] = output[i];
    }
    placement *= 10;
  }
  free(output);
  free(count);
}