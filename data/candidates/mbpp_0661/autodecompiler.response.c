int func0(int* nums, int numsSize) {
    int arr[numsSize];
    if (numsSize >= 2) arr[0] = nums[0];
    if (numsSize >= 3) arr[1] = nums[0] + nums[1];
    if (numsSize >= 3) {
        int x = arr[1] > nums[0] + nums[2] ? arr[1] : nums[0] + nums[2];
        arr[2] = x > nums[1] + nums[2] ? (arr[1] > nums[1] + nums[2] ? arr[1] : nums[1] + nums[2]) : nums[1] + nums[2];
    }
    for (int i = 3; ; i++) {
        if (i >= numsSize) break;
        int x = arr[i-1] > arr[i-2] + nums[i] ? arr[i-1] : arr[i-2] + nums[i];
        int y = x > arr[i-3] + nums[i-1] + nums[i] ? x : arr[i-3] + nums[i-1] + nums[i];
        arr[i] = y;
    }
    return arr[numsSize-1];
}