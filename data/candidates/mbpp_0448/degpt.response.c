int func0(int n)

{
  int iVar1;
  int d;
  int sum;
  int c;
  int b;
  int a;
  int n_local;
  undefined4 local_c;
  
  a = 3;
  b = 0;
  c = 2;
  if (n == 0) {
    local_c = 3;
  }
  else if (n == 1) {
    local_c = 3;
  }
  else if (n == 2) {
    local_c = 5;
  }
  else {
    sum = 5;
    for (n_local = n; 2 < n_local; n_local = n_local + -1) {
      iVar1 = a + b;
      sum = iVar1 + sum;
      a = b;
      b = c;
      c = iVar1;
    }
    local_c = sum;
  }
  return local_c;
}