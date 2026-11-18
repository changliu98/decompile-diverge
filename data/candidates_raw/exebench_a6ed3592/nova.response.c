static void func0(int n, char *s) {
    if (n == 0) {
        *s = '0';
        *(s + 1) = '\0';
        return;
    }
    int i = 0;
    int n_copy = n;
    while (n_copy) {
        n_copy /= 10;
        i++;
    }
    s[i--] = '\0';
    while (i >= 0) {
        s[i--] = (n % 10) + '0';
        n /= 10;
    }
}