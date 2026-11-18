void factor(int n, int *factors)

{
  double floor_sqrt = floor(sqrt(n));
  int p = 4;

  do {
    while (n % p) {
      if ((p -= 2) == 1)
        p = 2;
      else if (p == 4)
        p = 3;
      else
        p += 2;
      if (p > floor_sqrt)
        p = n;
    }
    n /= p;
    *(factors++) = p;
    *(factors++) = n;
  } while (n > 1);
}