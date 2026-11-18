int func0(int n,int x,int y)

{
  int local_20;
  int k;
  int ans;
  int y_local;
  int x_local;
  int n_local;
  
  ans = -0x80000000;
  for (k = 0; k <= n; k = k + 1) {
    if ((k % x == y) && (ans < k)) {
      ans = k;
    }
  }
  if ((ans < 0) || (n < ans)) {
    local_20 = -1;
  }
  else {
    local_20 = ans;
  }
  return local_20;
}