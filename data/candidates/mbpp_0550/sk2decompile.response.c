int _findMin(int *nums, int left, int right) {
  if (right < left) {
    return nums[0];
  }
  if (right == left) {
    return nums[left];
  }
  int mid = left + (right - left) / 2;
  if (mid < right && nums[mid + 1] < nums[mid]) {
    return nums[mid];
  }
  if (mid > left && nums[mid] < nums[mid - 1]) {
    return nums[mid - 1];
  }
  if (nums[left] <= nums[mid]) {
    return _findMin(nums, mid + 1, right);
  } else {
    return _findMin(nums, left, mid - 1);
  }
}