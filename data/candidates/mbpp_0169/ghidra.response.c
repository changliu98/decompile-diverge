int func0(int n)

{
  int iVar1;
  int i;
  int c;
  int b;
  int a;
  int n_local;
  undefined4 local_c;
  
  local_c = n;
  if (2 < n) {
    a = 1;
    b = 2;
    for (i = 3; i <= n; i = i + 1) {
      iVar1 = b * 2 + a;
      a = b;
      b = iVar1;
    }
    local_c = b;
  }
  return local_c;
}