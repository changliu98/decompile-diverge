int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int *ret, *a, *b, ret_c, a_c, b_c;
    int i, j, n, flag;

    ret = (int *)malloc(numsSize * sizeof(int));
    a = (int *)calloc(numsSize, sizeof(int));
    b = (int *)calloc(numsSize, sizeof(int));

    ret_c = 0;
    a_c = 0;
    b_c = 0;

    for (i = 0; i < numsSize; ++i) {
        flag = 0;
        n = nums[i];

        for (j = 0; j < b_c; ++j) {
            if (b[j] == n) {
                flag = 1;
                break;
            }
        }

        if (flag) continue;

        flag = 0;

        for (j = 0; j < a_c; ++j) {
            if (a[j] == n) {
                flag = 1;
                break;
            }
        }

        if (flag) {
            b[b_c++] = n;
        } else {
            a[a_c++] = n;
        }
    }

    for (i = 0; i < numsSize; ++i) {
        flag = 0;
        n = nums[i];

        for (j = 0; j < b_c; ++j) {
            if (b[j] == n) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            ret[ret_c++] = n;
        }
    }

    *returnSize = ret_c;

    free(a);
    free(b);

    return ret;
}