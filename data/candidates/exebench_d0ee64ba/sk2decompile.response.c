void simplify(int *num, int *den) {
  int i;
  int gcd;
  if (*num < *den && *num > 0) {
    i = *num;
  } else if (*den > 0) {
    i = *den;
  } else {
    i = *num;
  }
  while (i != 0) {
    if (*num % i == 0 && *den % i == 0) {
      gcd = i;
      i = 0;
    } else if (i > 0) {
      i--;
    } else {
      i++;
    }
  }
  if (gcd == -1) {
    gcd = 1;
  }
  *num = *num / gcd;
  *den = *den / gcd;
}