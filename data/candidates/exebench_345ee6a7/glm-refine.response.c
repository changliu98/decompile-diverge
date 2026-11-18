int __cdecl removeElement(int *nums, int numsSize, int val)
{
  int current_index = 0;
  
  while (current_index < numsSize)
  {
    if (nums[current_index] == val)
    {
      // Decrement the valid size and replace the current element
      // with the last valid element to "remove" the target value.
      numsSize--;
      nums[current_index] = nums[numsSize];
    }
    else
    {
      // Only move to the next index if the current element is kept.
      current_index++;
    }
  }
  
  return numsSize;
}