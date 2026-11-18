int * func0(int n)

{
  int *piVar1;
  int number;
  int original;
  int reversed;
  int i;
  int *counts;
  int n_local;
  
  piVar1 = malloc(8);
  *piVar1 = 0;
  piVar1[1] = 0;
  for (i = 1; i <= n; i = i + 1) {
    reversed = 0;
    for (number = i; number != 0; number = number / 10) {
      reversed = reversed * 10 + number % 10;
    }
    if (i == reversed) {
      if (i % 2 == 0) {
        *piVar1 = *piVar1 + 1;
      }
      else {
        piVar1[1] = piVar1[1] + 1;
      }
    }
  }
  return piVar1;
}