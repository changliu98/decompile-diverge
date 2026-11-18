int removeElement(int* nums, int numsSize, int val) {
    int i = 0;
    while (i < numsSize) {
        if (nums[i] == val) {
            numsSize--;
            nums[i] = nums[numsSize];
        } else {
            i++;
        }
    }
    return numsSize;
}