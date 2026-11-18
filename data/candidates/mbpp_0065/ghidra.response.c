int func0(int *data_list,int n)

{
  int iVar1;
  int iVar2;
  int sub_length;
  int i;
  int total;
  int n_local;
  int *data_list_local;
  
  total = 0;
  for (i = 0; i < n; i = i + 1) {
    if (data_list[i] < 0) {
      iVar1 = data_list[i];
      iVar2 = func0(data_list + (i + 1),-iVar1);
      i = -iVar1 + -1 + i + 1;
    }
    else {
      iVar2 = data_list[i];
    }
    total = iVar2 + total;
  }
  return total;
}