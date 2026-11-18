char* func0(int n) {
  static char str[32];
  int i = 0;
  int j;
  int k;
  char c;
  while (n > 0) {
    str[i++] = (n % 2) + '0';
    n /= 2;
  }
  str[i] = '\0';
  j = 0;
  k = i - 1;
  while (j < k) {
    c = str[j];
    str[j] = str[k];
    str[k] = c;
    j++;
    k--;
  }
  return str;
}