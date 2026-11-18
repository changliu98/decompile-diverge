int getPossibleCount(int *arr, int *out) {
    int count = 0;
    
    for (int i = 0; i < 9; i++) {
        if (arr[i] != 0) {
            count++;
            if (out != NULL) {
                *out = arr[i];
            }
        }
    }
    
    return count;
}