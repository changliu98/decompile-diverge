int func0(int n)

{
  int msb;
  int n_local;
  undefined4 local_c;
  
  if (n == 0) {
    local_c = 0;
  }
  else {
    msb = 0;
    while (n_local = n / 2, 0 < n_local) {
      msb = msb + 1;
      n = n_local;
    }
    local_c = 1 << ((byte)msb & 0x1f);
  }
  return local_c;
}