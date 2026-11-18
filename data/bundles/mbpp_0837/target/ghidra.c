int func0(int n)

{
  int i;
  int sum;
  int n_local;
  
  sum = 0;
  for (i = 0; i < n; i = i + 1) {
    sum = (i * 2 + 1) * (i * 2 + 1) * (i * 2 + 1) + sum;
  }
  return sum;
}