float func0(int a, int b) {
  int c = 0;
  int d = b;
  if (b == 0) {
    c = 1;
  } else {
    while (d != 0) {
      c++;
      d /= 10;
    }
  }
  return (double)a + (double)b / pow(10.0, (double)c);
}