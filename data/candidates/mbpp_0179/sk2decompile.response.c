bool _is_happy(int n) {
  int digits[100];
  int origin = n;
  int nn = n;
  int len = 0;
  while (nn > 0) {
    digits[len++] = nn % 10;
    nn /= 10;
  }
  int i = 0;
  int j = len - 1;
  while (i < j) {
    int tmp = digits[i];
    digits[i] = digits[j];
    digits[j] = tmp;
    i++;
    j--;
  }
  int sum = 0;
  int k = len;
  while (sum < origin) {
    sum = 0;
    for (int l = 1; l <= len; l++) {
      sum += digits[k - l];
    }
    digits[k++] = sum;
  }
  return sum == origin;
}