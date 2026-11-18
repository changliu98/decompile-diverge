void make_heap(int *rawheap, int size)
{
  int i = 0;
  int j = 0;
  int temp = 0;
  for (i = (size / 2 - 1); i >= 0; i--)
  {
    for (j = (2 * i + 1); j < size; j = (2 * j + 1))
    {
      if (j + 1 < size && (rawheap[j] > rawheap[j + 1]))
        j++;
      if (rawheap[i] <= rawheap[j])
        break;
      temp = rawheap[i];
      rawheap[i] = rawheap[j];
      rawheap[j] = temp;
      i = j - 1;
    }
  }
}