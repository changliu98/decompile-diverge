int func0(int *ar,int n)

{
  int iVar1;
  bool bVar2;
  int temp;
  int i_1;
  int step;
  int count;
  int i;
  int res;
  int n_local;
  int *ar_local;
  
  res = 0;
  for (step = 0; step < n + -1; step = step + 1) {
    for (i_1 = 0; i_1 < (n - step) + -1; i_1 = i_1 + 1) {
      if (ar[i_1 + 1] < ar[i_1]) {
        iVar1 = ar[i_1];
        ar[i_1] = ar[i_1 + 1];
        ar[i_1 + 1] = iVar1;
      }
    }
  }
  for (i = 0; i < n; i = i + 1) {
    count = 1;
    while( true ) {
      bVar2 = false;
      if (i + 1 < n) {
        bVar2 = ar[i] == ar[i + 1];
      }
      if (!bVar2) break;
      count = count + 1;
      i = i + 1;
    }
    if (res < count) {
      res = count;
    }
  }
  return res;
}