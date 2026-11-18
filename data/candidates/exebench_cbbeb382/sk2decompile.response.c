int factors(int n, int *f) {
  int i = 0;
  while (n % 53 == 0) {
    n /= 53;
    f[i] = 53;
    i++;
  }
  while (n % 47 == 0) {
    n /= 47;
    f[i] = 47;
    i++;
  }
  while (n % 43 == 0) {
    n /= 43;
    f[i] = 43;
    i++;
  }
  while (n % 41 == 0) {
    n /= 41;
    f[i] = 41;
    i++;
  }
  while (n % 37 == 0) {
    n /= 37;
    f[i] = 37;
    i++;
  }
  while (n % 31 == 0) {
    n /= 31;
    f[i] = 31;
    i++;
  }
  while (n % 29 == 0) {
    n /= 29;
    f[i] = 29;
    i++;
  }
  while (n % 23 == 0) {
    n /= 23;
    f[i] = 23;
    i++;
  }
  while (n % 19 == 0) {
    n /= 19;
    f[i] = 19;
    i++;
  }
  while (n % 17 == 0) {
    n /= 17;
    f[i] = 17;
    i++;
  }
  while (n % 13 == 0) {
    n /= 13;
    f[i] = 13;
    i++;
  }
  while (n % 11 == 0) {
    n /= 11;
    f[i] = 11;
    i++;
  }
  while (n % 8 == 0) {
    n /= 8;
    f[i] = 8;
    i++;
  }
  while (n % 7 == 0) {
    n /= 7;
    f[i] = 7;
    i++;
  }
  while (n % 5 == 0) {
    n /= 5;
    f[i] = 5;
    i++;
  }
  while (n % 4 == 0) {
    n /= 4;
    f[i] = 4;
    i++;
  }
  while (n % 3 == 0) {
    n /= 3;
    f[i] = 3;
    i++;
  }
  while (n % 2 == 0) {
    n /= 2;
    f[i] = 2;
    i++;
  }
  if (n > 31) {
    int j = 2;
    while (n > 1) {
      int p = 6 * j - 1;
      int q = 6 * j + 1;
      while (n % p == 0) {
        f[i] = p;
        i++;
        n /= p;
      }
      while (n % q == 0) {
        f[i] = q;
        i++;
        n /= q;
      }
      j++;
    }
  }
  return i;
}