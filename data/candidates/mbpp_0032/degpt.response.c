int func0(int n)

{
  double dVar1;
  int i;
  int maxPrime;
  int n_local;
  
  maxPrime = -1;
  for (n_local = n; n_local % 2 == 0; n_local = n_local >> 1) {
    maxPrime = 2;
  }
  for (i = 3; dVar1 = sqrt((double)n_local), (double)i <= dVar1; i = i + 2) {
    for (; n_local % i == 0; n_local = n_local / i) {
      maxPrime = i;
    }
  }
  if (2 < n_local) {
    maxPrime = n_local;
  }
  return maxPrime;
}