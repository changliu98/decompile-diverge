int func0(int n) {
    int i, j, k;
    k = 0;
    for (i = 0;; i++) {
        for (j = i; j < n; j++) {
            if (j % 11 == 0 || j % 13 == 0) {
                k++;
                j = j / 10;
                while (j > 0) {
                    if (j % 10 == 7) {
                        k++;
                    }
                    j = j / 10;
                }
            }
        }
    }
    return k;
}