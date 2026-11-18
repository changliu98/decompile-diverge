int func0(int *a, int n) {
    int i, j, k, max = 0, temp, max_index;
    max_index = a[0];
    for (i = 0; i < n; i++) {
        temp = 0;
        for (j = 0; j < n; j++) {
            if (a[j] == a[i]) {
                temp++;
            }
        }
        if (temp > max) {
            max = temp;
            max_index = a[i];
        }
    }
    return max_index;
}