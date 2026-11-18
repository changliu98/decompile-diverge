int func0(int *arr, int n) {
    int first_even = -1;
    int first_odd = -1;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0 && first_even == -1) {
            first_even = arr[i];
        }
        
        if (arr[i] % 2 != 0 && first_odd == -1) {
            first_odd = arr[i];
        }
        
        if (first_even != -1 && first_odd != -1) {
            break;
        }
    }
    
    return first_even * first_odd;
}