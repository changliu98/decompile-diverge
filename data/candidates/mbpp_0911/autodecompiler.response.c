int func0(int* nums, int numsSize) {
    int temp, product1, product2, i, j, k, ret;

    if (numsSize < 4) {
        ret = -1;
        goto end;
    }

    for (i = 0; i < numsSize - 1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if (nums[i] < nums[j]) {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    int highest = nums[0];
    int second_highest = nums[1];
    int third_highest = nums[2];
    int lowest = nums[numsSize - 1];
    int second_lowest = nums[numsSize - 2];

    product1 = highest * second_highest * third_highest;
    product2 = highest * lowest * second_lowest;

    ret = product1 > product2 ? product1 : product2;

end:
    return ret;
}