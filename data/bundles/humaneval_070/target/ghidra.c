void func0(int *lst,int size,int *out)

{
  int iVar1;
  int index;
  int r;
  int l;
  int temp;
  int j;
  int i;
  int *out_local;
  int size_local;
  int *lst_local;
  
  for (i = 0; j = i, i < size + -1; i = i + 1) {
    while (j = j + 1, j < size) {
      if (lst[j] < lst[i]) {
        iVar1 = lst[i];
        lst[i] = lst[j];
        lst[j] = iVar1;
      }
    }
  }
  r = size + -1;
  index = 0;
  for (l = 0; l <= r; l = l + 1) {
    if (l == r) {
      out[index] = lst[l];
      index = index + 1;
    }
    else {
      iVar1 = index + 1;
      out[index] = lst[l];
      index = index + 2;
      out[iVar1] = lst[r];
      r = r + -1;
    }
  }
  return;
}