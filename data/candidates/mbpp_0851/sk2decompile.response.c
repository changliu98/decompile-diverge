double func0(int a, int b) {
  double c;
  c = (double)b / (double)a;
  c *= 100;
  c = round(c);
  c /= 100;
  return c;
}