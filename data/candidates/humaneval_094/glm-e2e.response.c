int func0(int *arr, int n) {
    int max_prime = 0;
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        if (num > 1) {
            int is_prime = 1;
            for (int j = 2; j * j <= num; j++) {
                if (num % j == 0) {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime) {
                if (num > max_prime) {
                    max_prime = num;
                }
            }
        }
    }
    
    while (max_prime > 0) {
        sum += max_prime % 10;
        max_prime /= 10;
    }
    
    return sum;
}