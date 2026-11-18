int func0(int* nums, int numsSize) {
    int ans = 0;
    for (int i = 0; ; i++) {
        if (i >= numsSize) break;
        ans ^= nums[i];
    }
    return ans;
}