int func0(int n)

{
  int count;
  int n_local;
  
  count = 0;
  for (n_local = n; n_local != 0; n_local = n_local >> 1) {
    count = (n_local & 1U) + count;
  }
  return count;
}