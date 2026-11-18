int func0(int *nums, int size)
{
  int i; int j;
  int temp;
  int max = 0;
  if (size < 3)
    return -1;
  for (i = 0; i < size - 1; i++)
  {
    for (j = i + 1; j < size; j++)
    {
      if (nums[i] < nums[j])
      {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }
  if (nums[0]*nums[1]*nums[2] > nums[size - 3]*nums[size - 2]*nums[size - 1])
    return nums[0]*nums[1]*nums[2];
  else
    return nums[size - 3]*nums[size - 2]*nums[size - 1];
}