float func0(int a, int b) {
  int digits = 0;
  int temp = b;
  if (temp == 0) {
    digits = 1;
  } else {
    while (temp != 0) {
      digits++;
      temp /= 10;
    }
  }
  return a + b / pow(10, digits);
}