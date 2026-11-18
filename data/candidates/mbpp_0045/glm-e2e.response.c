int func0(int *arr, int n) {
    int g = find_gcd(arr[0], arr[1]);
    for (int i = 2; i < n; i++) {
        g = find_gcd(g, arr[i]);
    }
    return g;
}