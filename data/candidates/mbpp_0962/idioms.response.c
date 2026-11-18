int func0(int l, int r)
{
  int left = (l - 1) / 2;
  int right = r / 2;
  int left_sum = (left + 1) * (left + 1);
  int right_sum = (right + 1) * right;
  return right_sum - left_sum / 2;
}