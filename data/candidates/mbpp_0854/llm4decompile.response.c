void func0(int *rawheap, int size)
{
  int i;
  int j;
  int k;
  int temp;

  for (i = size / 2 - 1; i >= 0; i--) {
    for (j = i; j >= 0; j = k - 1) {
      k = j * 2 + 1;
      if (k >= size)
        break;
      if (k + 1 < size && rawheap[k] > rawheap[k + 1])
        k++;
      if (rawheap[j] <= rawheap[k])
        break;
      temp = rawheap[j];
      rawheap[j] = rawheap[k];
      rawheap[k] = temp;
    }
  }
}