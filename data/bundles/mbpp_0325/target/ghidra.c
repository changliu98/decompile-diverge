int func0(int n)

{
  int iVar1;
  int iVar2;
  int local_24;
  int temp;
  int x;
  int res;
  int n_local;
  int local_c;
  
  local_c = n;
  if (3 < n) {
    res = n;
    for (x = 1; (x <= n && (iVar1 = x * x, iVar1 <= n)); x = x + 1) {
      iVar2 = func0(n - iVar1);
      if (res < iVar2 + 1) {
        local_24 = res;
      }
      else {
        local_24 = func0(n - iVar1);
        local_24 = local_24 + 1;
      }
      res = local_24;
    }
    local_c = res;
  }
  return local_c;
}