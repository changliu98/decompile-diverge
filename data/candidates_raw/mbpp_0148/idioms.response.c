int sum_digits(int n)
{
  int closest_num = closest(n);
  int sum = sum_digits_single(closest_num);
  return sum + sum_digits_single(n - closest_num);
}