int mean3(int a, int b, int c, int max, int *err) {
  int m = (a + b + c) / 3;
  if (err) {
    int ea = (a - m > 0) ? a - m : m - a;
    int eb = (b - m > 0) ? b - m : m - b;
    int ec = (c - m > 0) ? c - m : m - c;
    *err = (ea > eb) ? ((a - m > 0) ? a - m : m - a)
                     : ((b - m > 0) ? b - m : m - b);
    *err = (ec > *err) ? ((a - m > 0) ? a - m : m - a)
                       : ((b - m > 0) ? b - m : m - b);
  }
  if (a < max && b < max && c < max) return m;
  return (m > max) ? m : max;
}