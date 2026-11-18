void func0(int *l, int size, int *out) {
    int *third = malloc(sizeof(int) * (size / 3 + 1));
    int third_size = 0;
    for (int i = 0; 3 * i < size; i++) {
        third[i] = l[3 * i];
        third_size++;
    }

    for (int i = 0; i < third_size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < third_size; j++) {
            if (third[j] < third[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = third[i];
            third[i] = third[min_idx];
            third[min_idx] = temp;
        }
    }

    for (int i = 0; i < size; i++) {
        if (i % 3 == 0) {
            out[i] = third[i / 3];
        } else {
            out[i] = l[i];
        }
    }
    free(third);
}