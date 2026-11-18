void shell_sort(int *array, int size)
{
  int gap = size;
  int i = 0;
  int j = 0;
  int temp = 0;
  int swapped = 1;
  while (1)
  {
    if (gap > 1 && !swapped)
      break;
    gap = (int)(gap / 1.3);
    swapped = 0;
    for (i = 0; i + gap < size; i++)
    {
      if (array[i] > array[i + gap])
      {
        temp = array[i];
        array[i] = array[i + gap];
        array[i + gap] = temp;
        swapped = 1;
      }
    }
  }
}