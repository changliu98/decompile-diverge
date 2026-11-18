__int64 __cdecl find_min_subarray_sum(__int64 *nums, int size)
{
  __int64 min_sum = nums[0];
  __int64 current_sum = nums[0];

  for (int i = 1; i < size; ++i)
  {
    // If the previous running sum is positive, reset the current sum to the current element.
    // Otherwise, extend the running sum by adding the current element.
    if (current_sum >= 0)
      current_sum = nums[i];
    else
      current_sum += nums[i];

    // Update the overall minimum if the current running sum is smaller
    if (current_sum < min_sum)
      min_sum = current_sum;
  }

  return min_sum;
}