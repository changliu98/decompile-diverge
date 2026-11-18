int __cdecl HPCC_factor235(int n, int *ip_0)
{
  int na;

  na = n;
  ip_0[0] = 0;
  ip_0[1] = 0;
  ip_0[2] = 0;

  // If n is not divisible by 2, 3, or 5, return 1 early
  if (n % 2 && n % 3 && n % 5)
    return 1;

  // If n is less than or equal to 1, return 1
  if (n <= 1)
    return 1;

  // Factor out all 2s
  while (na > 1 && (na & 1) == 0)
  {
    ++ip_0[0];
    na >>= 1;
  }

  // Factor out all 3s
  while (na > 1 && na % 3 == 0)
  {
    ++ip_0[1];
    na /= 3;
  }

  // Factor out all 5s
  while (na > 1 && na % 5 == 0)
  {
    ++ip_0[2];
    na /= 5;
  }

  // Return 1 if there is a remaining factor, 0 otherwise
  return na != 1;
}