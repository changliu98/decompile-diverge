void func0(int *lst1,int *lst2,int *res_list,int size)

{
  int i;
  int size_local;
  int *res_list_local;
  int *lst2_local;
  int *lst1_local;
  
  for (i = 0; i < size; i = i + 1) {
    res_list[i] = lst1[i] + lst2[i];
  }
  return;
}