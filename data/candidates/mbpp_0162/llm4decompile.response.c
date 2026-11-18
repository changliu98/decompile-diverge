int func0(int n) {
  int result;
  if (n > 0) {
    result = n + func0(n - 2);
  } else {
    result = 0;
  }
  return result;
}