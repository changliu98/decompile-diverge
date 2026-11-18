void chartobit(int n, char s[]) {
    int i;
    for (i = BITS_IN_CHAR - 1; i >= 0; i--, n /= 2)
        s[i] = (01 & n) + '0';
}