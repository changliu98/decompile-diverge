int divide(int a, int b, int *remainder) {
  *remainder = a % b;
  int result = a / b;
  return result;
}