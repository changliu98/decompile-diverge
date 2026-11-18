bool __checkPalindrome(int *digits, int n, int k) {
  int i, sum = 0;
  for (i = 0; i < n / 2; i++) {
    if (digits[i] != digits[n - 1 - i]) return false;
    sum += digits[i] + digits[n - 1 - i];
  }
  if (n % 2 == 1) sum += digits[n / 2];
  return sum <= k;
}