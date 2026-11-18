int func0(int i) {
    int j;
    for (j = 0; j < n; j++) {
        if (a[j][0] == i) {
            return a[j][1];
        }
    }
    return 1;
}