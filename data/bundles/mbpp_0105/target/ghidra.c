int func0(int *lst,int size)

{
  int i;
  int total;
  int size_local;
  int *lst_local;
  
  total = 0;
  for (i = 0; i < size; i = i + 1) {
    total = lst[i] + total;
  }
  return total;
}