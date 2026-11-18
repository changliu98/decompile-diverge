int find(float* arr, int n, float target) {
    if (target < arr[0]) {
        return 0;
    }
    if (target >= arr[n - 1]) {
        return n - 1;
    }
    
    int mid = 0;
    int left = 1;
    int right = n;
    
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (target >= arr[mid - 1]) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return left - 1;
}