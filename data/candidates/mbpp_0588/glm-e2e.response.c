int func0(int *arr, int n) {
    int max_val = -2147483648; // 0x80000000
    int min_val = 2147483647;  // 0x7fffffff
    int i = 0;
    
    while (i < n) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        i++;
    }
    
    return max_val - min_val;
}