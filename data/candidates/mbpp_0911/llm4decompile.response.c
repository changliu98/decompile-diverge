int func0(int *nums, int size)
{
    if (size < 3)
        return -1;
    int i, j, temp;
    for (i = 0; i < size - 1; i++)
        for (j = i + 1; j < size; j++)
            if (nums[i] < nums[j])
                temp = nums[i], nums[i] = nums[j], nums[j] = temp;
    int max1 = nums[0] * nums[1] * nums[2];
    int max2 = nums[0] * nums[size - 1] * nums[size - 2];
    return max1 > max2 ? max1 : max2;
}