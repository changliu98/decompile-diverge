int func0(int *arr,int x,int n)

{
  int iVar1;
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
    iVar1 = (low + high) / 2;
    if (x < arr[iVar1]) {
      high = iVar1 + -1;
    }
    else if (arr[iVar1] < x) {
      low = iVar1 + 1;
    }
    else {
      high = iVar1 + -1;
      res = iVar1;
    }
  }
  return res;
}