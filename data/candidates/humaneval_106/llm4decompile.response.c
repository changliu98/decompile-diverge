int * func0(int n) {
    int *arr = malloc(sizeof(int) * n);
    int sum = 0;
    int prod = 1;
    for (int i = 1; i <= n; i++) {
        sum += i;
        prod *= i;
        if (i % 2 == 0) {
            arr[i - 1] = prod;
        } else {
            arr[i - 1] = sum;
        }
    }
    return arr;
}