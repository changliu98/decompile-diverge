int func0(int *nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, mid, res = -1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (target == nums[mid]) {
            res = mid;
            right = mid - 1;
        } else if (target < nums[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return res;
}