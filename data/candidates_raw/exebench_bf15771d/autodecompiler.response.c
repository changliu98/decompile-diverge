int getSum(int *arr, int *len) {
  int sum = 0;
  int maxLen = 0;
  int maxLenSum = 0;

  int i = 0;
  int twoPowerI = 1;

  while (1) {
    if (twoPowerI / 2 >= *len) break;
    if (arr[i] > 0) {
      sum += arr[i];
      if (sum > twoPowerI / 2) {
        maxLen = twoPowerI;
        maxLenSum = sum;
      }
    } else if (sum == *len) break;

    i++;
    twoPowerI *= 2;
  }

  *len = maxLen;
  return maxLenSum;
}