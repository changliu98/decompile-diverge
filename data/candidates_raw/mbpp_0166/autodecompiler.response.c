int input6_get_even_count(int *arr, int size) {
    int i, j;
    int evenPair = 0;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if ((arr[i] ^ arr[j]) % 2 == 0) {
                evenPair++;
            }
        }
    }
    return evenPair;
}