char* func0(int a, int b, int c) {
  int x, y;
  for (x = 0; x * a <= c; x++) {
    y = (c - x * a) / b;
    if (y * b + x * a == c) {
      sprintf(buf, "x = %d, y = %d", x, y);
      return buf;
    }
  }
  return "No solution";
}