void func0(int *list1, int list1_size, int *list2, int list2_size, int *list_result)
{
  int i;
  int j;
  for(i = 0; i < list1_size - 1; i++)
  {
    list_result[i] = list1[i];
  }
  for(j = 0; j < list2_size; j++)
  {
    list_result[list1_size + j - 1] = list2[j];
  }
}