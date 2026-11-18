char summe(int *n, int *s) {
 if (*n == 0) {
  return 1;
 }
 *s += *n;
 *n -= 1;
 if (summe(n, s)) {
  return 1;
 }
 return 0;
}