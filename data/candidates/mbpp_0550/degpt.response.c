int func0(int *nums, int left, int right)
{
    // Base case: if the range is invalid, return the first element of the array
    if (right < left) {
        return *nums;
    }
    // Base case: if the range has only one element, return that element
    if (right == left) {
        return nums[left];
    }
    // Calculate the middle index to avoid potential overflow
    int middle = left + (right - left) / 2;
    // Check if the right neighbor is smaller than the middle element, indicating a peak at mid
    if (middle < right && nums[middle + 1] < nums[middle]) {
        return nums[middle];
    }
    // Check if the left neighbor is larger than the middle element, indicating a peak at mid-1
    if (left < middle && nums[middle] < nums[middle - 1]) {
        return nums[middle - 1];
    }
    // If the middle element is smaller than the low element, the peak is in the left half
    if (nums[middle] < nums[left]) {
        return func0(nums, left, middle - 1);
    }
    // Otherwise, the peak is in the right half
    return func0(nums, middle + 1, right);
}