float func0(int *a, int *b, size_t n) {
    int i = 0;
    int j = 0;
    int prev = -1;
    int curr = -1;
    int k = 0;
    
    while (k < n + 1) {
        k++;
        if (i == n) {
            prev = curr;
            curr = b[0];
            break;
        }
        if (j == n) {
            prev = curr;
            curr = a[0];
            break;
        }
        if (a[i] <= b[j]) {
            prev = curr;
            curr = a[i];
            i++;
        } else {
            prev = curr;
            curr = b[j];
            j++;
        }
    }
    
    return (prev + curr) / 2.0;
}