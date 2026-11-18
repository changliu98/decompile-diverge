int func0(int* nums, int numsSize) {
    char found_duplicate = 0;
    int i = 0;
    int j;

    while (1) {
        if (i >= numsSize) break;

        j = i + 1;

        while (1) {
            if (j >= numsSize) break;

            if (nums[i] == nums[j]) {
                found_duplicate = 1;
                break;
            } else {
                j++;
            }
        }

        if (found_duplicate & 0x01) break;
        i++;
    }

    return found_duplicate;
}