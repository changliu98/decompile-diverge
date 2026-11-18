int func0(int a[], int n) {
    int i, j, k, sum = 0;
    for (i = 0, j = 0;; i++) {
        for (k = 1; k < n; k++) {
            if (a[k] == a[i] && k!= i)
                j++;
            else
                continue;
        }
        if (k > 1)
            sum = sum + a[i];
        else
            continue;
    }
    return sum;
}