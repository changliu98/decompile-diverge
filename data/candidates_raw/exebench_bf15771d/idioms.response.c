int get_max_sum(int *nums, int *max_sum)
{
  int sum = 0;
  int max = 0;
  int max_sum_val = 0;
  int i = 0;
  int twotoi = 1;
  while (twotoi / 2 < *max_sum)
  {
    if (nums[i] > 0)
    {
      sum += nums[i];
      if (sum > twotoi / 2)
      {
        max = twotoi;
        max_sum_val = sum;
      }
    }
    if (sum == *max_sum)
      break;
    i++;
    twotoi = twotoi * 2;
  }
  *max_sum = max;
  return max_sum_val;
}