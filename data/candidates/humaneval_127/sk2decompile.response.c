char* is_prime(int x1, int y1, int x2, int y2) {
  int x, y, d;
  if (x1 > x2)
    x = x1;
  else
    x = x2;
  if (y1 < y2)
    y = y1;
  else
    y = y2;
  d = y - x;
  if (d < 2) return "YES";
  int i;
  for (i = 2; i * i <= d; i++) {
    if (d % i == 0) return "YES";
  }
  return "NO";
}