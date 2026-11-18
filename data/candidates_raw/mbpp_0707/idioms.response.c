int count_set_bits(int n)
{
  int i; int j; int k;
  int count = n + 1;
  for (i = 2, j = (count / i); i <= count; i *= 2, j = (count / i))
  {
    count += i * (j / 2);
    if (count % i != 0)
      count += (count % i);
  }
  return count;
}