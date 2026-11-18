int func0(int x) {
    int n = x + 1;
    char buf[16];

    while (n < 0x7fffffff) {
        sprintf(buf, "%d", n);
        int len = strlen(buf);
        int is_palindrome = 1;
        for (int i = 0; i < len / 2; i++) {
            if (buf[i] != buf[len - 1 - i]) {
                is_palindrome = 0;
                break;
            }
        }
        if (is_palindrome) {
            return n;
        }
        n++;
    }
    return -1;
}