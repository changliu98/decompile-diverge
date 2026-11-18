void shell_sort(int *my_list, int length)
{
  int gap = length / 2;
  while (gap > 0)
  {
    int i = gap;
    while (i < length)
    {
      int j = i;
      int current_item = my_list[i];
      int should_swap = 0;
      while (j >= gap && (should_swap = (my_list[j - gap] > current_item)))
      {
        my_list[j] = my_list[j - gap];
        j -= gap;
      }
      my_list[j] = current_item;
      i++;
    }
    gap = gap / 2;
  }
}