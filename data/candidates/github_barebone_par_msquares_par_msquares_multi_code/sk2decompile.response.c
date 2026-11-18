int par_msquares_multi_code(int a, int b, int c, int d) {
  int m = 1;
  int a1, b1, c1, code;
  if (b == a) {
    a1 = 0;
  } else {
    m = 2;
    a1 = 1;
  }
  if (c == b) {
    b1 = a1;
  } else if (c == a) {
    b1 = 0;
  } else {
    b1 = m++;
  }
  if (d == c) {
    c1 = b1;
  } else if (d == b) {
    c1 = a1;
  } else if (d == a) {
    c1 = 0;
  } else {
    c1 = m;
  }
  code = (c1 << 6) | (b1 << 4) | (a1 << 2) | m;
  return code;
}