int func0(int n)

{
  int sum;
  int i;
  int n_local;
  
  sum = 0;
  for (i = 1; 0 < n / i; i = i << 1) {
    sum = sum + n / i;
  }
  return sum;
}