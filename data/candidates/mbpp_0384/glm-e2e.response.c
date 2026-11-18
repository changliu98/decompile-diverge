int func0(int n, int *arr) {
    int min_val = arr[0];
    int count = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            count = 1;
        } else if (arr[i] == min_val) {
            count++;
        }
    }
    
    return count;
}