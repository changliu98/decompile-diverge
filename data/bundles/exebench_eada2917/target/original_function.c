int
HPCC_factor235(int n, int *ip) {
  ip[0] = ip[1] = ip[2] = 0;

  if (n % 2 != 0 && n % 3 != 0 && n % 5 != 0)
    return 1;

  if (n <= 1)
    return 1;


  for (; n > 1 && ! (n & 1); n >>= 1)
    ip[0]++;


  for (; n > 1 && ! (n % 3); n /= 3)
    ip[1]++;


  for (; n > 1 && ! (n % 5); n /= 5)
    ip[2]++;

  if (n != 1)
    return 1;

  return 0;
}