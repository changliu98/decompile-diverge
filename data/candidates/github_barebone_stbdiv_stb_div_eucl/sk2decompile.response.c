int stb_div_eucl(int a, int b) {
  int q, r;
  if (a >= 0) {
    if (b >= 0) return a / b;
    if (b == -2147483647 - 1) {
      q = 0;
      r = a;
    } else {
      q = -(a / -b);
      r = a % -b;
    }
  } else {
    if (a == -2147483647 - 1) {
      if (b >= 0) {
        q = -(-(a + b) / b) - 1;
        r = -(-(a + b) % b);
      } else if (b == -2147483647 - 1) {
        q = 1;
        r = 0;
      } else {
        q = (b - a) / -b + 1;
        r = -((b - a) % -b);
      }
    } else if (b >= 0) {
      q = -(-a / b);
      r = -(-a % b);
    } else if (b == -2147483647 - 1) {
      q = 1;
      r = a - b;
    } else {
      q = -a / -b;
      r = -(-a % -b);
    }
  }
  if (r < 0) q += b > 0 ? -1 : 1;
  return q;
}