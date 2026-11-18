void func0(int *arr, int n) {
    int exp = 1;
    int max_val = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    int *output = malloc(n * 4);
    int *count = malloc(40); // 10 * 4 bytes
    
    while (exp <= max_val) {
        for (int i = 0; i < 10; i++) {
            count[i] = 0;
        }
        
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }
        
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
        
        exp *= 10;
    }
    
    free(output);
    free(count);
}