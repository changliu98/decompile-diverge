int func0(int *arr, int low, int high) {
    int mid;
    int result;
    
    if (high < low) {
        result = arr[0];
        return result;
    }
    
    if (high == low) {
        result = arr[low];
        return result;
    }
    
    mid = low + (high - low) / 2;
    
    if (mid < high && arr[mid + 1] < arr[mid]) {
        result = arr[mid];
        return result;
    }
    
    if (mid > low && arr[mid] < arr[mid - 1]) {
        result = arr[mid - 1];
        return result;
    }
    
    if (arr[low] <= arr[mid]) {
        result = func0(arr, low, mid - 1);
        return result;
    }
    
    result = func0(arr, mid + 1, high);
    return result;
}