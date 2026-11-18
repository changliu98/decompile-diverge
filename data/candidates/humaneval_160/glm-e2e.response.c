int func0(char **operations, int *nums, int n, int operations_count) {
    int *values = (int *)malloc(sizeof(int) * operations_count);
    int *indices = (int *)malloc(sizeof(int) * operations_count);

    for (int i = 0; i < operations_count; i++) {
        values[i] = nums[i];
        indices[i] = i;
    }

    for (int i = 0; i < operations_count; i++) {
        if (strcmp(operations[i], "XOR") == 0) {
            while (indices[indices[i]] != indices[i]) {
                indices[i] = indices[indices[i]];
            }
            while (indices[indices[i + 1]] != indices[i + 1]) {
                indices[i + 1] = indices[indices[i + 1]];
            }
            values[indices[i]] = (int)pow((double)values[indices[i]], (double)values[indices[i + 1]]);
            indices[i + 1] = indices[i];
        }
    }

    for (int i = 0; i < operations_count; i++) {
        if (strcmp(operations[i], "MUL") == 0 || strcmp(operations[i], "DIV") == 0) {
            while (indices[indices[i]] != indices[i]) {
                indices[i] = indices[indices[i]];
            }
            while (indices[indices[i + 1]] != indices[i + 1]) {
                indices[i + 1] = indices[indices[i + 1]];
            }
            if (strcmp(operations[i], "MUL") == 0) {
                values[indices[i]] *= values[indices[i + 1]];
            } else {
                values[indices[i]] /= values[indices[i + 1]];
            }
            indices[i + 1] = indices[i];
        }
    }

    for (int i = 0; i < operations_count; i++) {
        if (strcmp(operations[i], "ADD") == 0 || strcmp(operations[i], "SUB") == 0) {
            while (indices[indices[i]] != indices[i]) {
                indices[i] = indices[indices[i]];
            }
            while (indices[indices[i + 1]] != indices[i + 1]) {
                indices[i + 1] = indices[indices[i + 1]];
            }
            if (strcmp(operations[i], "ADD") == 0) {
                values[indices[i]] += values[indices[i + 1]];
            } else {
                values[indices[i]] -= values[indices[i + 1]];
            }
            indices[i + 1] = indices[i];
        }
    }

    int result = values[0];
    free(values);
    free(indices);

    return result;
}