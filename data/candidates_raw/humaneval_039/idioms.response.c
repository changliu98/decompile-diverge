int p100(int n)
{
  struct bigint a = {2, 0};
  int i = 0;
  int isprime;
  int p;
  while (i < n) {
    a = add(a);
    isprime = 1;
    for (p = 2; p * p <= a.hi; p++)
      if (a.hi % p == 0) {
        isprime = 0;
        break;
      }
    if (isprime)
      i++;
    if (i == n)
      return a.hi;
  }
  return 0;
}