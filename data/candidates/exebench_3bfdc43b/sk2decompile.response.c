void norm(int *q, int *r, int m) {
  int k;
  if (*r < 0) {
    k = (-*r - 1) / m + 1;
    *q -= k;
    *r += k * m;
  }
  if (*r >= m) {
    k = *r / m;
    *q += k;
    *r -= k * m;
  }
}