void func0(int *lst1, int *lst2, int *res_list, int size)
{
  int i;
  for (i = 0; i < size; i++)
    res_list[i] = lst1[i] + lst2[i];
}