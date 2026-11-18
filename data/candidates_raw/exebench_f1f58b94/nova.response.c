void func0(struct Array *arr) {
    int i, j;
    for (i = 0; i < arr->length - 1; i++) {
        for (j = 0; j < arr->length - i - 1; j++) {
            if (arr->A[j] > arr->A[j + 1]) {
                Swap(&arr->A[j], &arr->A[j + 1]);
            }
        }
    }
}