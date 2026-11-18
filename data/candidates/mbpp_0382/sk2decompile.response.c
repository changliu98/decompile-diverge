int _find_min_index(int* nums, int numsSize) {
  int left = 0;
  int right = numsSize - 1;
  while (left <= right) {
    if (nums[left] <= nums[right]) {
      return left;
    }
    int mid = (left + right) / 2;
    if (nums[mid] <= nums[(mid + 1) % numsSize] &&
        nums[mid] <= nums[(mid + numsSize - 1) % numsSize]) {
      return mid;
    }
    if (nums[mid] > nums[right]) {
      if (nums[mid] >= nums[left]) {
        left = mid + 1;
      }
    } else {
      right = mid - 1;
    }
  }
  return -1;
}