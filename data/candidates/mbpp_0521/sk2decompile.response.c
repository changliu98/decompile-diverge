bool __is_distinct(int a, int b, int c) {
  if (a == b) {
    return false;
  }
  if (b == c) {
    return false;
  }
  if (c == a) {
    return false;
  }
  return true;
}