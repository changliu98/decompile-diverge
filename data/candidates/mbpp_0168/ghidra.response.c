int func0(int *a,int n,int x)

{
  int i;
  int count;
  int x_local;
  int n_local;
  int *a_local;
  
  count = 0;
  for (i = 0; i < n; i = i + 1) {
    if (a[i] == x) {
      count = count + 1;
    }
  }
  return count;
}