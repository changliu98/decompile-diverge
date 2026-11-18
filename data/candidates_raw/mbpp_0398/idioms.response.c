int sum_of_digit(int *nums, int length)
{
  int sum = 0;
  int i;
  int n;
  for (i = 0; i < length; i++) {
    n = nums[i];
    if (n < 0)
      n = -n;
    while (n > 0) {
      sum += n % 10;
      n /= 10;
    }
  }
  return sum;
}