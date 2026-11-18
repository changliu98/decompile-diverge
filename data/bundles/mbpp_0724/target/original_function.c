int func0(int base, int power) {
  int digits[1000];
  int size = 1;
  digits[0] = 1;
  for (int p = 0; p < power; p++) {
    int carry = 0;
    for (int i = 0; i < size; i++) {
      long temp = (long)digits[i] * base + carry;
      digits[i] = temp % 10;
      carry = temp / 10;
    }
    while (carry > 0) {
      digits[size] = carry % 10;
      carry /= 10;
      size++;
    }
  }
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += digits[i];
  }
  return sum;
}