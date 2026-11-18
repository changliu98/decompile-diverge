void kf_factor(int n, int *factors) {
  int n1 = n;
  int f = 4;
  double sqrtn = floor(sqrt((double)n));
  do {
    while (n1 % f) {
      if (f == 2)
        f = 3;
      else if (f == 4)
        f = 2;
      else
        f += 2;
      if (f > sqrtn) f = n1;
    }
    n1 /= f;
    *factors++ = f;
    *factors++ = n1;
  } while (n1 > 1);
}