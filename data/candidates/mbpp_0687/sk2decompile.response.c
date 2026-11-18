int func0(int a, int b) {
  int min, max;
  if (a < b)
    min = a;
  else
    min = b;
  if (a > b)
    max = a;
  else
    max = b;
  if (min == 0) return max;
  if (min == 1) return 1;
  return func0(min, max % min);
}