bool func0(int *arr, int n) {
    bool is_valid = true;
    
    if (n == 0) {
        is_valid = true;
    } else {
        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[i - 1]) {
                is_valid = false;
                break;
            }
            if (i >= 2) {
                if (arr[i] == arr[i - 1] && arr[i] == arr[i - 2]) {
                    is_valid = false;
                    break;
                }
            }
        }
    }
    
    return is_valid;
}