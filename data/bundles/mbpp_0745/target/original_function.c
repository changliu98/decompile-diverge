void func0(int startnum, int endnum, int result[], int *result_size) {
  *result_size = 0;
  for (int n = startnum; n <= endnum; ++n) {
    bool divisible = true;
    int temp = n;
    while (temp > 0) {
      int digit = temp % 10;
      if (digit == 0 || n % digit != 0) {
        divisible = false;
        break;
      }
      temp /= 10;
    }
    if (divisible) {
      result[*result_size] = n;
      (*result_size)++;
    }
  }
}