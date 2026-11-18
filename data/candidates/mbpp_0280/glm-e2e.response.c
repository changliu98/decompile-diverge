bool func0(int *arr, int n, int target, int *index) {
    *index = 0;
    bool found = false;
    
    while (*index < n) {
        if (arr[*index] == target) {
            found = true;
            break;
        }
        (*index)++;
    }
    
    return found;
}