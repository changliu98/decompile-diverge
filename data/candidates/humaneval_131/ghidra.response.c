int func0(int n)

{
  bool bVar1;
  undefined4 local_1c;
  int digit;
  int has_odd;
  int prod;
  int n_local;
  
  prod = 1;
  bVar1 = false;
  for (n_local = n; 0 < n_local; n_local = n_local / 10) {
    if ((n_local % 10) % 2 == 1) {
      bVar1 = true;
      prod = (n_local % 10) * prod;
    }
  }
  if (bVar1) {
    local_1c = prod;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}