void kf_factor(int n, int *buf)
{
  int na = n;
  int p = 4;
  double floor_sqrt = floor(sqrt((double) n));
  do {
    while (na % p != 0) {
      if (p == 2)
        p = 3;
      else if (p == 4)
        p = 2;
      else
        p += 2;
      if (p > floor_sqrt)
        p = na;
    }
    na /= p;
    *buf++ = p;
    *buf++ = na;
  } while (na > 1);
}