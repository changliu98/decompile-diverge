int func0(int n,int x,int y)

{
  bool bVar1;
  int i;
  int isp;
  int y_local;
  int x_local;
  int n_local;
  int local_c;
  
  bVar1 = 1 < n;
  for (i = 2; i * i <= n; i = i + 1) {
    if (n % i == 0) {
      bVar1 = false;
    }
  }
  local_c = y;
  if (bVar1) {
    local_c = x;
  }
  return local_c;
}