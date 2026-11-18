bool func0(const char **arr1, const char **arr2, int size1, int size2) {
    const char *intersection[100];
    const char *res1[100];
    const char *res2[100];
    int inter_size = 0;
    int res1_size = 0;
    int res2_size = 0;

    // Find the intersection of arr1 and arr2
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (strcmp(arr1[i], arr2[j]) == 0) {
                bool is_dup = false;
                for (int k = 0; k < inter_size; k++) {
                    if (strcmp(intersection[k], arr1[i]) == 0) {
                        is_dup = true;
                        break;
                    }
                }
                if (!is_dup) {
                    intersection[inter_size++] = arr1[i];
                }
            }
        }
    }

    // Build res1 from arr1 elements that are in the intersection
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < inter_size; j++) {
            if (strcmp(arr1[i], intersection[j]) == 0) {
                res1[res1_size++] = arr1[i];
            }
        }
    }

    // Build res2 from arr2 elements that are in the intersection
    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < inter_size; j++) {
            if (strcmp(arr2[i], intersection[j]) == 0) {
                res2[res2_size++] = arr2[i];
            }
        }
    }

    // Check if the sizes of the two result arrays are equal
    if (res1_size != res2_size) {
        return false;
    }

    // Check if the elements in the two result arrays match in order
    for (int i = 0; i < res1_size; i++) {
        if (strcmp(res1[i], res2[i]) != 0) {
            return false;
        }
    }

    return true;
}