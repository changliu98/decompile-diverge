bool func0(int *arr, int n, int target) {
    int left = 0;
    int right = n - 1;
    int found = 0;
    
    while (left <= right && !found) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            found = 1;
        } else if (target < arr[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return found;
}