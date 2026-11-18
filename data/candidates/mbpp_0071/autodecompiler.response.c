void func0(int *a, int array_size)
{
  int i, j, temp;
  float shrink = 1.3;
  int gap = array_size;
  int swapped = 1;

  while ((gap > 1) || (swapped > 0)) {
    if (gap > 1)
      gap = (int) ((float) gap / shrink);

    swapped = 0;

    for (i = 0; i + gap < array_size; i++) {
      j = i + gap;

      if (a[i] > a[j]) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        swapped = 1;
      }
    }
  }
}