Optimized for reverse engineering readability
void __cdecl func0(int *lst1, int *lst2, int *res_list, int size)
{
  // Performs element-wise addition of two integer arrays (lst1 and lst2)
  // and stores the result in res_list.
  for (int i = 0; i < size; ++i)
  {
    res_list[i] = lst1[i] + lst2[i];
  }
}