bool sboxCHECK(float *arr1, float *arr2, int size) {
    if (arr1 == NULL || arr2 == NULL) {
        return true;
    }

    for (int i = 0; i < size; i++) {
        if (arr1[i] > arr2[i]) {
            return false;
        }
    }

    return true;
}