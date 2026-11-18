int func0(int *arr, int n) {
    int result;
    int sum = 0;
    int sign = 1;
    int i;

    if (n == 0) {
        result = -32768; // 0xffff8000 in 32-bit signed integer
    } else {
        for (i = 0; i < n; i++) {
            sum += abs(arr[i]);
            
            if (arr[i] == 0) {
                sign = 0;
            }
            
            if (arr[i] < 0) {
                sign = -sign;
            }
        }
        result = sum * sign;
    }
    
    return result;
}