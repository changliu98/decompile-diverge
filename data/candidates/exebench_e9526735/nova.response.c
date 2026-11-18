void removeslave(int *s, int n) {
    int i = 9;
    while (1) {
        if (i < 0)
            return;
        if (s[i]) {
            s[i] = 0;
            n--;
            if (n == 0)
                return;
        }
        i--;
    }
}