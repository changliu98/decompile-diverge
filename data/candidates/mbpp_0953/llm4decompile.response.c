int func0(int *ar, int n) {
    int step, i, count, res = 0;

    for (step = 0; step < n - 1; step++) {
        for (i = 0; i < n - step - 1; i++) {
            if (ar[i] > ar[i + 1]) {
                int temp = ar[i];
                ar[i] = ar[i + 1];
                ar[i + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        count = 1;
        while (i + 1 < n && ar[i] == ar[i + 1]) {
            count++;
            i++;
        }
        if (count > res) {
            res = count;
        }
    }

    return res;
}