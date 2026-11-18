int func0(int *list, int n)
{
  int first_even = -1;
  int first_odd = -1;
  int i;
  for (i = 0; i < n; i++) {
    if (list[i] % 2 == 0 && first_even == -1)
      first_even = list[i];
    if (list[i] % 2 != 0 && first_odd == -1)
      first_odd = list[i];
    if (first_even != -1 && first_odd != -1)
      break;
  }
  return (first_even * first_odd);
}