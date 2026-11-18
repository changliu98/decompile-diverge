int func0(int p) {
  int a, b, c, max = 0;
  for (c = 1; c < p - 1; c++) {
    for (b = 1; b < p; b++) {
      a = p - c - b;
      if (a * b * c > max) max = a * b * c;
    }
  }
  return max;
}