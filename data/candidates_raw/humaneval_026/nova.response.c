int *func0(int *nums1, int nums1Size, int *returnSize) {
    int *nums2 = (int *)malloc(nums1Size * sizeof(int));
    int *nums3 = (int *)calloc(nums1Size, sizeof(int));
    int *nums4 = (int *)calloc(nums1Size, sizeof(int));
    int i, j, k, l;
    int flag;
    int flag2;
    for (i = 0; i < nums1Size; i++) {
        for (j = 0; j < i; j++) {
            if (nums1[i] == nums1[j]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            for (k = 0; k < nums1Size; k++) {
                if (nums1[k] == nums1[i]) {
                    flag2 = 1;
                    break;
                }
            }
            if (flag2) {
                nums2[k] = nums1[i];
            } else {
                nums3[i] = nums1[i];
            }
        } else {
            for (l = 0; l < nums1Size; l++) {
                if (nums1[l] == nums1[i]) {
                    flag2 = 1;
                    break;
                }
            }
            if (flag2) {
                nums4[l] = nums1[i];
            }
        }
    }
    *returnSize = nums4[0];
    free(nums2);
    free(nums3);
    return nums4;
}