void SwapIEEE32(char *x) {
  char t;
  t = x[0];
  x[0] = x[3];
  x[3] = t;
  t = x[1];
  x[1] = x[2];
  x[2] = t;
}