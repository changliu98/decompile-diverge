int func0(int a, int n, int l, int r)
{
  int count = 0;
  for ( ; l <= r; l++) {
    if (l % a == 0)
      count++;
    if (count == n)
      break;
  }
  return l;
}