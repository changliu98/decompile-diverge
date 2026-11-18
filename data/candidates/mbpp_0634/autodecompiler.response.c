int func0(int n)
{
  int total = 0;
  int i = 1;
  int j;

  while (1) {
    if (i > n) break;
    j = i * 2;
    total += j * j * j * j;
    i++;
  }

  return total;
}