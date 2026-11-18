int func0(int n) {
    int i, j, k, count = 0;
    for (i = 1;; i++) {
        for (j = i;; j = j / 2) {
            if (j == 0)
                break;
            if (j % 2 == 0)
                count++;
        }
        if (count == n)
            break;
    }
    return i;
}