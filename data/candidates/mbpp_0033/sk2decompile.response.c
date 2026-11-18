int func0(int n) {
  int i, j, k, l;
  k = 0;
  l = 0;
  while (n != 0) {
    j = 1;
    for (i = 0; i < l; i++) j *= 10;
    k += (n % 2) * j;
    n /= 2;
    l++;
  }
  return k;
}