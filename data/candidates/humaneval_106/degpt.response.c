int * func0(int n)

{
  int *piVar1;
  int i;
  int prod;
  int sum;
  int *out;
  int n_local;
  
  piVar1 = malloc((long)n << 2);
  sum = 0;
  prod = 1;
  for (i = 1; i <= n; i = i + 1) {
    sum = i + sum;
    prod = i * prod;
    if (i % 2 == 0) {
      piVar1[i + -1] = prod;
    }
    else {
      piVar1[i + -1] = sum;
    }
  }
  return piVar1;
}