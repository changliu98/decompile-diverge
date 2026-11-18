int func0(int n)

{
  int i;
  int sum;
  int n_local;
  
  sum = 0;
  for (i = 1; i <= n; i = i + 1) {
    sum = i * i * i * i + sum;
  }
  return sum;
}