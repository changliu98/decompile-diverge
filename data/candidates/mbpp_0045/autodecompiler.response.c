int func0(int *arr, int size) {
    int i;
    int gcd = find_gcd(arr[0], arr[1]);
    for (i = 2; ; i++) {
        if (i >= size) {
            break;
        }
        gcd = find_gcd(gcd, arr[i]);
    }
    return gcd;
}