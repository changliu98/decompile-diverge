int func0(int *a, int *b, int n) {
    sort(a, n);
    sort(b, n);

    int sum = 0;
    int i = 0;
    while (1) {
        if (i < n) {
            sum += abs(a[i] - b[i]);
            i++;
        } else {
            break;
        }
    }
    return sum;
}