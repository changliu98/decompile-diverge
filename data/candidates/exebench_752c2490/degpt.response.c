int valid(int *a,int n)

{
  bool local_21;
  int i;
  int n_local;
  int *a_local;
  
  i = 0;
  do {
    if (n + -2 <= i) {
      local_21 = true;
      if (a[n + -1] == 0) {
        local_21 = a[n + -2] != 0;
      }
      return (uint)((local_21 ^ 0xffU) & 1);
    }
    if (a[i] < 1) {
      if (a[i] < 0) {
        return 0;
      }
    }
    else {
      a[i + 2] = a[i + 2] + a[i] * -3;
      a[i + 1] = a[i + 1] + a[i] * -2;
      a[i] = 0;
    }
    i = i + 1;
  } while( true );
}