int rob(int* nums, int numsSize) {
    int ret;
    if (numsSize == 1)
        ret = nums[0];
    else {
        int arr[numsSize];
        arr[0] = nums[0];
        arr[1] = ((nums[0])>(nums[1])?(nums[0]):(nums[1]));
        for (int i = 2; ; ++i) {
            if (i >= numsSize)
                break;
            int x = arr[i - 1];
            int y = arr[i - 2] + nums[i];
            int z = nums[i];
            arr[i] = ((x)>(y)?(x):(y));
            arr[i] = ((arr[i])>(z)?(arr[i]):(z));
        }
        ret = arr[numsSize - 1];
    }
    return ret;
}