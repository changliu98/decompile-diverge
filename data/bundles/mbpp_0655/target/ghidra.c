int func0(int n)

{
  int i;
  int sm;
  int n_local;
  
  sm = 0;
  for (i = 1; i <= n; i = i + 1) {
    sm = i * i * i * i * i + sm;
  }
  return sm;
}