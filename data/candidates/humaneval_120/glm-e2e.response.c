void func0(int *arr1, int size, int k, int *arr2) {
    int i, j, temp;
    
    // Bubble sort to sort arr1 in ascending order
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                temp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = temp;
            }
        }
    }
    
    // Copy the last 'k' elements from arr1 to arr2
    for (i = 0; i < k; i++) {
        arr2[i] = arr1[size - k + i];
    }
}