int func0(int n)

{
  int count;
  int n_local;
  undefined4 local_c;
  
  count = 0;
  n_local = n;
  if ((n == 0) || (local_c = n, (n & n - 1U) != 0)) {
    for (; n_local != 0; n_local = n_local >> 1) {
      count = count + 1;
    }
    local_c = 1 << ((byte)count & 0x1f);
  }
  return local_c;
}