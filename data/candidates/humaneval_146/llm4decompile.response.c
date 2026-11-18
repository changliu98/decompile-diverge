int func0(int nums[], int size)
{
    int i;
    int count = 0;
    for (i = 0; i < size; i++) {
        if (nums[i] > 10) {
            int tmp = nums[i];
            while (tmp / 10 >= 1) {
                tmp = tmp / 10;
            }
            if (tmp % 2 == 1 && nums[i] % 10 % 2 == 1) {
                count++;
            }
        }
    }
    return count;
}