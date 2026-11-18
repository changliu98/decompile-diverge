const char* func0(int a, int b, int c) {
  if ((b * b) - (4 * a * c) > 0) {
    return "2 solutions";
  } else if ((b * b) - (4 * a * c) == 0) {
    return "1 solution";
  } else {
    return "No solutions";
  }
}