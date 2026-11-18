void func0(int *arr1, int n, int *arr2) {
    int *temp = malloc((n / 3 + 1) * 4);
    int count = 0;
    int i, j, min_idx;

    for (i = 0; i < n; i += 3) {
        temp[count] = arr1[i];
        count++;
    }

    for (i = 0; i < count - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < count; j++) {
            if (temp[j] < temp[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int t = temp[i];
            temp[i] = temp[min_idx];
            temp[min_idx] = t;
        }
    }

    for (i = 0; i < n; i++) {
        if (i % 3 == 0) {
            arr2[i] = temp[i / 3];
        } else {
            arr2[i] = arr1[i];
        }
    }

    free(temp);
}