int func0(int n) {
    int i, j, k;
    if (n < 11)
        k = 0;
    else {
        j = 1;
        i = 1;
        while (i <= n) {
            if (i <= n) {
                j = j * i;
                j = j % 100;
            }
            i++;
        }
        k = j;
    }
    return k;
}