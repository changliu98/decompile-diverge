int _day_of_week(int y) {
  int a = y / 100;
  int b = y / 400;
  int c = y / 2;
  int d = y - c;
  if (a) {
    d += a;
    c -= a;
  }
  if (b) {
    d -= b;
    c += b;
  }
  return (2 * c + d) % 7;
}