void arraylist_sort_internal(void *data, int length, int (*compare)(void *data1, void *data2))
{
  if (length > 1)
  {
    int pivot = length - 1;
    int i;
    int j = 0;
    void *temp;
    void *pivotData = ((void *)data + (pivot * sizeof(void *)));
    for (i = 0; i < pivot; i++)
    {
      if (compare(((void *)data + (i * sizeof(void *))), pivotData) < 0)
      {
        temp = ((void *)data + (i * sizeof(void *)));
        ((void *)data + (i * sizeof(void *))) = ((void *)data + (j * sizeof(void *)));
        ((void *)data + (j * sizeof(void *))) = temp;
        j++;
      }
    }
    ((void *)data + (pivot * sizeof(void *))) = ((void *)data + (j * sizeof(void *)));
    ((void *)data + (j * sizeof(void *))) = pivotData;
    arraylist_sort_internal(data, j, compare);
    arraylist_sort_internal(((void *)data + ((j + 1) * sizeof(void *))), length - j - 1, compare);
  }
}