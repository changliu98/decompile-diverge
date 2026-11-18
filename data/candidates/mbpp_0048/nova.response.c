int func0(int n) {
    int i = 0, ans = 0, m = n;
    while (m > 0) {
        if (i % 2 == 0)
            ans = ans | (1 << i);
        i++;
        m = m >> 1;
    }
    return ans | n;
}