double frexp(double x, int *exp) {
  int sign = 1;
  int power;
  double result;
  if (x < 0) {
    sign = -1;
    x = -x;
  } else if (x == 0) {
    *exp = 0;
    return 0;
  }
  *exp = 0;
  power = 1;
  result = x;
  while (result >= 0.5 || result >= 1) {
    power *= 2;
    (*exp)++;
    result = x / power;
  }
  return sign * result;
}