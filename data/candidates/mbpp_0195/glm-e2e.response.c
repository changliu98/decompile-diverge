int func0(int* arr, int target, int size) {
    int low = 0;
    int high = size - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] > target) {
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            result = mid;
            high = mid - 1;
        }
    }
    
    return result;
}