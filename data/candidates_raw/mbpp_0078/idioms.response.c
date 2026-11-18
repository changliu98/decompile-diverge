int f(int n)
{
  if (n % 2 == 0) {
    int count = 0;
    int i;
    for (i = 0; i < 32; i++)
      count += (n >> i) & 1;
    n = n / 2;
    if (count % 2 == 1)
      n++;
    return n;
  } else
    return (n + 1) / 2;
}