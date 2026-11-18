int func0(int n)

{
  int i;
  int f [1000];
  int n_local;
  
  memset(f,0,4000);
  f[0] = 0;
  f[1] = 1;
  for (i = 2; i <= n; i = i + 1) {
    f[i] = f[i + -1] + f[i + -2];
  }
  return f[n];
}