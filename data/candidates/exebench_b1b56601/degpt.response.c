void nexper(int n,int *a,int *mtc,int *even)

{
  int iVar1;
  int iVar2;
  int m;
  int i1;
  int l;
  int ia;
  int j2;
  int j1;
  int nm3;
  int j;
  int i;
  int d;
  int s;
  int *even_local;
  int *mtc_local;
  int *a_local;
  int n_local;
  
  if (*mtc == 0) {
    for (i = 1; i <= n; i = i + 1) {
      a[i] = i;
    }
    *mtc = 1;
    *even = 1;
  }
  else if (*even == 1) {
    iVar1 = a[1];
    a[1] = a[2];
    a[2] = iVar1;
    *even = 0;
    if ((a[n] == 1) && (a[1] == n % 2 + 2)) {
      if (n < 4) {
        *mtc = 0;
      }
      else {
        for (i = 1; i <= n + -3; i = i + 1) {
          if (a[i + 1] != a[i] + 1) {
            return;
          }
        }
        *mtc = 0;
      }
    }
  }
  else {
    s = 0;
    for (i1 = 2; i1 <= n; i1 = i1 + 1) {
      iVar1 = a[i1];
      iVar2 = i1 + -1;
      d = 0;
      for (j = 1; j <= iVar2; j = j + 1) {
        if (iVar1 < a[j]) {
          d = d + 1;
        }
      }
      s = d + s;
      if (d != iVar2 * (s % 2)) {
        m = ((s + 1) % 2) * (n + 1);
        for (j = 1; j <= iVar2; j = j + 1) {
          if (((-1 < a[j] - iVar1) && (a[j] - m < 0)) || ((a[j] - iVar1 < 0 && (-1 < a[j] - m)))) {
            m = a[j];
            l = j;
          }
        }
        a[l] = iVar1;
        a[i1] = m;
        *even = 1;
        return;
      }
    }
    *mtc = 0;
  }
  return;
}