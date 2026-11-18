void kf_factor(int n, int *facbuf)
{
  int p=4;
  double floor_sqrt = floor( sqrt((double)n) );

  do {
    while (n % p) {
      switch (p) {
      case 4: p = 2; break;
      case 2: p = 3; break;
      default: p += 2; break;
      }
      if (p > floor_sqrt)
 p = n;
    }
    n /= p;
    *facbuf++ = p;
    *facbuf++ = n;
  } while (n > 1);
}