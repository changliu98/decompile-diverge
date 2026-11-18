int func0(int n)

{
  int i;
  int ff [100];
  int n_local;
  
  memset(ff,0,400);
  ff[1] = 0;
  ff[2] = 1;
  for (i = 3; i <= n; i = i + 1) {
    ff[i] = ff[i + -1] + ff[i + -2] + ff[i + -3];
  }
  return ff[n];
}