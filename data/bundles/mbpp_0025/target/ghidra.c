int func0(int *arr,int n)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int prod;
  int temp;
  int j;
  int i;
  int n_local;
  int *arr_local;
  
  prod = 1;
  for (i = 1; i < n; i = i + 1) {
    iVar1 = arr[i];
    iVar3 = i;
    while( true ) {
      j = iVar3 + -1;
      bVar2 = false;
      if (-1 < j) {
        bVar2 = iVar1 < arr[j];
      }
      if (!bVar2) break;
      arr[iVar3] = arr[j];
      iVar3 = j;
    }
    arr[iVar3] = iVar1;
  }
  for (i = 0; i < n; i = i + 1) {
    if ((i == 0) || (arr[i + -1] != arr[i])) {
      prod = arr[i] * prod;
    }
  }
  return prod;
}