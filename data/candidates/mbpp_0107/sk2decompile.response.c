int func0(int a, int b) {
  int count = 0;
  int temp;
  for (; a <= b; a++) {
    if (a >= 10 && a <= 15) {
      count++;
    } else if (a > 15) {
      temp = a;
      while (temp) {
        if (temp % 16 >= 10) {
          count++;
        }
        temp /= 16;
      }
    }
  }
  return count;
}