bool func0(int n) {
  int i, temp, count;
  for (i = 0; i < 10; i++) {
    temp = n;
    count = 0;
    while (temp > 0) {
      if (temp % 10 == i) {
        count++;
      }
      if (count > i) {
        return false;
      }
      temp /= 10;
    }
  }
  return true;
}