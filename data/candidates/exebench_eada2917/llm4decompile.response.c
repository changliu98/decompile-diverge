int HPCC_factor235(u64 n, int *ip)
{
  ip[0] = ip[1] = ip[2] = 0;

  if (n % 2 != 0 && n % 3 != 0 && n % 5 != 0)
    return 1;

  while (n > 1) {
    if (n % 2 == 0) {
      ip[0]++;
      n /= 2;
    } else if (n % 3 == 0) {
      ip[1]++;
      n /= 3;
    } else if (n % 5 == 0) {
      ip[2]++;
      n /= 5;
    } else
      break;
  }

  return (n == 1) ? 0 : 1;
}