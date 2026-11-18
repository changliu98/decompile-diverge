int findMin(int *nums, int numsSize)
{
 int i;
 int min = -1;

 for (i = 1; ; i++)
 {
  if (i >= numsSize)
   break;
  if (nums[i] < nums[i - 1])
  {
   min = i;
  }
 }

 return min;
}