int func0(int *nums, int numsSize) {
    int i = 0;
    int j = 0;
    int count = 0;
    while (j < numsSize) {
        if (nums[j] > 0) {
            count++;
        } else {
            int temp = 0;
            int n = abs(nums[j]);
            while (n >= 10) {
                temp += n % 10;
                n /= 10;
            }
            temp -= n;
            if (temp > 0) {
                count++;
            }
        }
        j++;
    }
    return count;
}