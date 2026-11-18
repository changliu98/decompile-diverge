void swap(int *a)

{
  int max;
  int maxn;
  int i;
  int min;
  int minn;
  int *a_local;
  
  minn = 0;
  for (i = 0; i < 10; i = i + 1) {
    if (a[i] < *a) {
      minn = i;
    }
  }
  maxn = 0;
  for (i = 0; i < 10; i = i + 1) {
    if (*a < a[i]) {
      maxn = i;
    }
  }
  *a = *a + a[minn];
  a[minn] = *a - a[minn];
  *a = *a - a[minn];
  a[9] = a[9] + a[maxn];
  a[maxn] = a[9] - a[maxn];
  a[9] = a[9] - a[maxn];
  return;
}