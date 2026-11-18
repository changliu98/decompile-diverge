int * func0(int n)

{
  int *piVar1;
  int i;
  int *out;
  int n_local;
  
  piVar1 = malloc((long)(n + 1) << 2);
  *piVar1 = 1;
  if (n != 0) {
    piVar1[1] = 3;
    for (i = 2; i <= n; i = i + 1) {
      if (i % 2 == 0) {
        piVar1[i] = i / 2 + 1;
      }
      else {
        piVar1[i] = piVar1[i + -1] + piVar1[i + -2] + 1 + (i + 1) / 2;
      }
    }
  }
  return piVar1;
}