int func0(int v, int t) {
  double w = 0;
  w = -11.37 * pow(v, 0.16) + 13.12 * 1 + .6215 * t + 32;
  w = round(w + 0.3965 * t * pow(v, 0.16));
  return (int)w;
}