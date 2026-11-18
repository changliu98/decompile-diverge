int func0(int n)

{
  int i;
  int count;
  int n_local;
  
  count = 0;
  for (i = 1; i <= n; i = i + 1) {
    if (n % i == 0) {
      count = count + 1;
    }
  }
  return count;
}