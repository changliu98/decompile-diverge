int func0(char **argv, int argc) {
    int i, j, k, l, m, n;
    char *p;

    if (argc == 0)
        return 0;
    i = j = k = 0;
    while (k < argc) {
        p = argv[k];
        l = 0;
        while (p[l]) {
            if (isalpha(p[l])) {
                i = 0;
                break;
            }
            if (!(isprint(p[l]) & 0x400))
                i = 1;
            if (isprint(p[l]) & 0x200)
                j = 1;
            if (i + j == 2) {
                i = 0;
                break;
            }
            l++;
        }
        k++;
    }
    return i;
}