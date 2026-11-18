int func0(int *arr, int left, int target) {
    int right = left;
    int mid;
    
    while (right >= 0) {
        mid = (right + left) / 2;
        if (arr[mid] < target) {
            right = mid + 1;
        } else {
            left = mid;
        }
    }
    
    return right;
}