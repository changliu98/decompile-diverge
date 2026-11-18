struct Pair** func0(int** arr, int n, int* arr2, int target, int* count) {
    struct Pair** result = malloc(0x320); // 800 bytes
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = arr2[i] - 1; j >= 0; j--) {
            if (arr[i][j] == target) {
                result[k] = malloc(sizeof(struct Pair));
                result[k]->first = i;
                result[k]->second = j;
                k++;
            }
        }
    }
    *count = k;
    return result;
}