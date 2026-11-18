int func0(int *arr, int left, int right) {
    if (left > right) {
        return right + 1;
    }
    
    if (arr[left] != left) {
        return left;
    }
    
    int mid = (left + right) / 2;
    
    if (arr[mid] == mid) {
        return func0(arr, mid + 1, right);
    } else {
        return func0(arr, left, mid);
    }
}