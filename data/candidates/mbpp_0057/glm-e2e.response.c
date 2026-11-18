int func0(int *arr, int size) {
    int i, j, temp;
    
    // Sort array in descending order (selection sort style)
    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
    // Concatenate digits to form the largest number
    int result = arr[0];
    for (int k = 1; k < size; k++) {
        result = result * 10 + arr[k];
    }
    
    return result;
}