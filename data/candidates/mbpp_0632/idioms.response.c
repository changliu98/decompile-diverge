void func0(int *num_list, int size, int *new_list)
{
  int zero_count = 0;
  int i = 0;
  int j = 0;
  for (i = 0; i < size; i++)
  {
    if (num_list[i] == 0)
    {
      zero_count++;
    }
    else
    {
      new_list[j++] = num_list[i];
    }
  }
  for (i = 0; i < zero_count; i++)
  {
    new_list[j++] = 0;
  }
}