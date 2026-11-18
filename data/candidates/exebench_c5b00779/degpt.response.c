int Fibonacci_search(int *a,int n,int key)

{
  int iVar1;
  int iVar2;
  int k;
  int i;
  int mid;
  int high;
  int low;
  int F [13];
  int key_local;
  int n_local;
  int *a_local;
  
  memcpy(F,&DAT_00102010,0x34);
  low = 1;
  k = 0;
  while (i = n, F[k] + -1 < n) {
    k = k + 1;
  }
  for (; high = n, i < F[k] + -1; i = i + 1) {
    a[i] = a[n];
  }
  while( true ) {
    while( true ) {
      if (high < low) {
        return 0;
      }
      iVar1 = low + F[k + -1];
      iVar2 = iVar1 + -1;
      if (a[iVar2] <= key) break;
      high = iVar1 + -2;
      k = k + -1;
    }
    if (key <= a[iVar2]) break;
    k = k + -2;
    low = iVar1;
  }
  if (n < iVar2) {
    return n;
  }
  return iVar2;
}