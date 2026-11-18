int binary_search(int* arr, int n, int target) {
    int left = 0;
    int right = n - 1;
    int result = -1; // Initialized to -0xffffffff which is -1 for a 32-bit int
    int mid;

    while (left <= right) {
        mid = left + (right - left) / 2;
        
        if (arr[mid] > target) {
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            result = mid;
            break;
        }
    }
    
    return result;
}