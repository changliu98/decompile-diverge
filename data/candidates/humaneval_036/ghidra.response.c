int func0(int n)

{
  int q;
  int i;
  int count;
  int n_local;
  
  count = 0;
  for (i = 0; i < n; i = i + 1) {
    if ((i % 0xb == 0) || (i % 0xd == 0)) {
      for (q = i; 0 < q; q = q / 10) {
        if (q % 10 == 7) {
          count = count + 1;
        }
      }
    }
  }
  return count;
}