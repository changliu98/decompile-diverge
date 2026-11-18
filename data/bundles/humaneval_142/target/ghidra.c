int func0(int *lst,int size)

{
  int iVar1;
  int i;
  int sum;
  int size_local;
  int *lst_local;
  
  sum = 0;
  for (i = 0; i < size; i = i + 1) {
    if (i % 3 == 0) {
      iVar1 = lst[i] * lst[i];
    }
    else if (i % 4 == 0) {
      iVar1 = lst[i] * lst[i] * lst[i];
    }
    else {
      iVar1 = lst[i];
    }
    sum = iVar1 + sum;
  }
  return sum;
}