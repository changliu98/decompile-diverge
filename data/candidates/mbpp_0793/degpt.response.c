int func0(int *arr,int x,int n)

{
  int iVar1;
  int iVar2;
  int mid;
  int res;
  int high;
  int low;
  int n_local;
  int x_local;
  int *arr_local;
  
  low = 0;
  high = n + -1;
  res = -1;
  while (low <= high) {
    iVar2 = (low + high) / 2;
    if (x < arr[iVar2]) {
      high = iVar2 + -1;
    }
    else {
      iVar1 = iVar2;
      if (arr[iVar2] < x) {
        iVar1 = res;
      }
      res = iVar1;
      low = iVar2 + 1;
    }
  }
  return res;
}