int func0(int n)

{
  int i;
  int out;
  int n_local;
  undefined4 local_c;
  
  if (n < 1) {
    local_c = 0;
  }
  else if (n == 1) {
    local_c = 1;
  }
  else {
    out = 0x12;
    for (i = 2; i < n; i = i + 1) {
      out = out * 10;
    }
    local_c = out;
  }
  return local_c;
}