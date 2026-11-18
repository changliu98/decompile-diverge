int findMin(int *nums, int numsSize)
{
 int left = 0, right = numsSize - 1, mid;

 while (left <= right) {
  if (nums[left] <= nums[right])
   return(left);
  mid = (left + right) / 2;
  int next = (mid + 1) % numsSize;
  int prev = (mid - 1 + numsSize) % numsSize;

  if (nums[mid] <= nums[next] && nums[mid] <= nums[prev])
   return(mid);

  if (nums[mid] <= nums[right])
   right = mid - 1;
  else if (nums[mid] >= nums[left])
   left = mid + 1;
 }
 return(-1);
}