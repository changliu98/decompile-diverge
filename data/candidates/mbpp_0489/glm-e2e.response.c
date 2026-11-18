int func0(int n, int *arr) {
    int max_val = arr[0];
    int count = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            count = 1;
        } else if (arr[i] == max_val) {
            count++;
        }
    }
    
    return count;
}