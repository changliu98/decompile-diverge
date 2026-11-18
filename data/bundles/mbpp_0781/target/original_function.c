char* func0(int n) {
  int count = 0;
  for (int i = 1; i < ((int)sqrt(n)) + 2; i++) {
    if (n % i == 0) {
      if (n / i == i) {
        count++;
      } else {
        count += 2;
      }
    }
  }
  if (count % 2 == 0) {
    return "Even";
  } else {
    return "Odd";
  }
}