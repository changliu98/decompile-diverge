int arrayFind(int target, int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            // Shift elements to the left
            for (int j = 0; j < i; j++) {
                arr[i - j] = arr[i - j - 1];
            }
            // Place the target at the beginning of the array
            arr[0] = target;
            return 0;
        }
    }
    return -1;
}