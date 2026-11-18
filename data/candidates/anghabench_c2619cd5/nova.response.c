int binary_search(int *arr, int size, int target) {
    int low = 0, high = size - 1;
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] > target) {
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}