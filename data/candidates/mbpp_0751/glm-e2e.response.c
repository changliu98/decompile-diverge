bool func0(int *arr, int size, int index) {
    if (2 * index + 2 > size) {
        return true;
    }
    
    bool left_valid;
    if (arr[index] > arr[2 * index + 1]) {
        left_valid = false;
    } else {
        left_valid = func0(arr, size, 2 * index + 1);
    }
    
    bool right_valid = true;
    if (2 * index + 2 != size) {
        if (arr[index] > arr[2 * index + 2]) {
            right_valid = false;
        } else {
            right_valid = func0(arr, size, 2 * index + 2);
        }
    }
    
    return left_valid && right_valid;
}