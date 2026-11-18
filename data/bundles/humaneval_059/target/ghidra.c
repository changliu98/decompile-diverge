int func0(int n)

{
  int i;
  int n_local;
  
  n_local = n;
  for (i = 2; i * i <= n_local; i = i + 1) {
    for (; n_local % i == 0 && i < n_local; n_local = n_local / i) {
    }
  }
  return n_local;
}