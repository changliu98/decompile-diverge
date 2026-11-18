int func0(int a, int b, int c) {
  int smallest;
  if (a <= b && a <= c) {
    smallest = a;
  } else if (b <= a && b <= c) {
    smallest = b;
  } else {
    smallest = c;
  }
  return smallest;
}