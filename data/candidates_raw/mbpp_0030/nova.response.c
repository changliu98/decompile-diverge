int func0(char *s) {
    int i, j, k, l, m, n;
    int res = 0;

    l = strlen(s);
    for (i = 0; i < l; i++) {
        for (j = 1; j <= l - i; j++) {
            if (is_palindrome(s, i, i + j - 1)) {
                res++;
            } else {
                break;
            }
        }
    }

    return res;
}