int func0(int *nums, int numsSize) {
    int sum = 0;
    int i = 0;
    int flag = 0;
    while (1) {
        if (i < numsSize) {
            sum += nums[i];
            if (sum < 0) {
                flag = 1;
                break;
            }
        } else {
            break;
        }
        i++;
    }
    return flag;
}