int * func0(int n)

{
  int *piVar1;
  int i;
  int *out;
  int n_local;
  
  piVar1 = malloc((long)n << 2);
  *piVar1 = n;
  for (i = 1; i < n; i = i + 1) {
    piVar1[i] = piVar1[(long)i + -1] + 2;
  }
  return piVar1;
}