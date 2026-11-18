int func0(int *a,int n)

{
  int j;
  int mx;
  int n_local;
  int *a_local;
  
  mx = -0x80000000;
  j = 1;
  while( true ) {
    if (n <= j) {
      return 1;
    }
    if (a[j] < mx) break;
    if (mx < a[j + -1]) {
      mx = a[j + -1];
    }
    j = j + 1;
  }
  return 0;
}