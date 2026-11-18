void func0(int *arr1, int *arr2, int *arr3, int *out, int len1, int len2, int len3) {
    int min_diff = 0x7fffffff;
    int i = 0, j = 0, k = 0;
    int best_i = 0, best_j = 0, best_k = 0;

    while (i < len1 && j < len2 && k < len3) {
        int min_val;
        if (arr1[i] < arr2[j]) {
            if (arr1[i] < arr3[k]) {
                min_val = arr1[i];
            } else {
                min_val = arr3[k];
            }
        } else {
            if (arr2[j] < arr3[k]) {
                min_val = arr2[j];
            } else {
                min_val = arr3[k];
            }
        }

        int max_val;
        if (arr1[i] > arr2[j]) {
            if (arr1[i] > arr3[k]) {
                max_val = arr1[i];
            } else {
                max_val = arr3[k];
            }
        } else {
            if (arr2[j] > arr3[k]) {
                max_val = arr2[j];
            } else {
                max_val = arr3[k];
            }
        }

        int diff = max_val - min_val;
        if (diff < min_diff) {
            min_diff = diff;
            best_i = i;
            best_j = j;
            best_k = k;
        }

        if (min_diff == 0) {
            break;
        }

        if (arr1[i] == min_val) {
            i++;
        } else if (arr2[j] == min_val) {
            j++;
        } else {
            k++;
        }
    }

    out[0] = arr1[best_i];
    out[1] = arr2[best_j];
    out[2] = arr3[best_k];
}