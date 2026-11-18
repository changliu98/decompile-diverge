int func0(int *arr, int n) {
    // Sort the array in ascending order using Bubble Sort
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    int result = -1;
    
    // Traverse the sorted array backwards to find the largest palindrome
    for (int i = n - 1; i >= 0; i--) {
        if (is_palindrome(arr[i])) {
            result = arr[i];
            break;
        }
    }
    
    return result;
}