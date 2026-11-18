int *func0(int *nums1, int nums1Size, int *nums2, int nums2Size,
               int *returnSize) {
    int *nums = (int *)malloc(sizeof(int) * nums1Size);
    int i = 0, j = 0;
    for (; i < nums1Size; i++) {
        for (j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                nums[i] = nums1[i];
                break;
            }
        }
        if (j < nums2Size) {
            break;
        }
    }
    int k = 0;
    for (j = 0; j < nums1Size - i - 1; j++) {
        if (nums[k] > nums[k + 1]) {
            int temp = nums[k];
            nums[k] = nums[k + 1];
            nums[k + 1] = temp;
        } else {
            k++;
        }
    }
    *returnSize = i;
    return nums;
}