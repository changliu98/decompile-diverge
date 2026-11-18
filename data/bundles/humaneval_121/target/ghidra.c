int func0(int *lst,int size)

{
  int i;
  int sum;
  int size_local;
  int *lst_local;
  
  sum = 0;
  for (i = 0; i * 2 < size; i = i + 1) {
    if (lst[i << 1] % 2 == 1) {
      sum = lst[i << 1] + sum;
    }
  }
  return sum;
}