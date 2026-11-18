void func0(int *arr, int n, struct Result *res) {
    int sum = 0;
    int product = 1;
    
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        product *= arr[i];
    }
    
    res->sum = sum;
    res->product = product;
}