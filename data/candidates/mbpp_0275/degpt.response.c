int func0(int *a,int n,int m)

{
  int maxx;
  int result;
  int i;
  int m_local;
  int n_local;
  int *a_local;
  
  for (i = 0; i < n; i = i + 1) {
    a[i] = a[i] / m + (uint)(a[i] % m != 0);
  }
  result = -1;
  maxx = -1;
  while (i = n + -1, -1 < i) {
    n = i;
    if (maxx < a[i]) {
      maxx = a[i];
      result = i;
    }
  }
  return result + 1;
}