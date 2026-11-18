int findMin(int *nums, int numsSize)
{
 sortArray(nums, numsSize);

 int i, min, max, tmp;
 int count = 0;
 max = 0;
 min = numsSize;
 for (i = 0; ; )
 {
  if (i >= numsSize - 1)
   break;

  if (nums[i] == nums[i + 1])
  {
   count++;
  }
  else
  {
   if (max < count)
    max = count;
   if (min > count)
    min = count;
   count = 0;
  }

  i++;
 }

 return max - min;
}