int func0(int* nums, int numsSize) {
    int max_ending_here = 1;
    int min_ending_here = 1;
    int max_so_far = 0;
    int flag = 0;

    for (int i = 0; ; ++i) {
        if (i >= numsSize)
            break;

        if (nums[i] > 0) {
            max_ending_here *= nums[i];
            int temp = min_ending_here * nums[i] < 1 ? min_ending_here * nums[i] : 1;
            min_ending_here = temp;
            flag = 1;
        } else if (nums[i] == 0) {
            max_ending_here = 1;
            min_ending_here = 1;
        } else {
            int temp = max_ending_here;
            max_ending_here = min_ending_here * nums[i] > 1 ? min_ending_here * nums[i] : 1;
            min_ending_here = temp * nums[i];
        }

        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
    }

    int result;
    if (!flag && !max_so_far)
        result = 0;
    else
        result = max_so_far;

    return result;
}