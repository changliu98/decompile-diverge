int func0(int n) {
    int ans = 0, i = 0, j = n;
    while (j > 0) {
        if (j % 2 == 0)
            ans = ans | 1 << i;
        i++;
        j = j >> 1;
    }
    return ans ^ n;
}