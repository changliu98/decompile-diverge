int func0(int *nums, int numsSize) {
    int count = 0;
    int i = 0, j = 0;
    while (i < numsSize) {
        j = i + 1;
        while (j < numsSize) {
            if ((nums[i] ^ nums[j]) % 3 == 0)
                count++;
            j++;
        }
        i++;
    }
    return count;
}