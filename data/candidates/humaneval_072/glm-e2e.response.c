bool func0(int *arr, int n, int t) {
    int sum = 0;
    int i = 0;
    
    while (i < n / 2) {
        if (arr[i] != arr[n - 1 - i]) {
            return false;
        }
        sum += arr[i] + arr[n - 1 - i];
        i++;
    }
    
    if (n % 2 == 1) {
        sum += arr[n / 2];
    }
    
    return sum <= t;
}