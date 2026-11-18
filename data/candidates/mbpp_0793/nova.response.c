int func0(int *nums, int target, int numsSize) {
    int left = 0, right = numsSize - 1, mid;
    int result = -1;

    while (left <= right) {
        mid = (left + right) / 2;
        if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            result = mid;
            left = mid + 1;
        }
    }

    return result;
}