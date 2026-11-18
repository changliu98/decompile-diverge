int func0(int n)

{
  int x;
  int count;
  int n_local;
  
  count = 0;
  for (x = 1; x < n + 1; x = x << 1) {
    if ((x & n) == 0) {
      count = count + 1;
    }
  }
  return count;
}