int _016(int base, int power) {
  int digits[1000];
  int num_digits = 1;
  digits[0] = 1;
  int i, j;
  for (j = 0; j < power; j++) {
    int carry = 0;
    for (i = 0; i < num_digits; i++) {
      long long product = (long long)digits[i] * base + carry;
      digits[i] = product % 10;
      carry = product / 10;
    }
    while (carry > 0) {
      digits[num_digits] = carry % 10;
      carry /= 10;
      num_digits++;
    }
  }
  int sum = 0;
  for (i = 0; i < num_digits; i++) {
    sum += digits[i];
  }
  return sum;
}