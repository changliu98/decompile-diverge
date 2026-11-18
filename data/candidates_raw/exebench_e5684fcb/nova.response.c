int func0(char *s) {
    char *p = s;
    char *q = s;
    while (1) {
        while (*q) {
            q++;
        }
        q--;
        q--;
        while (p < q) {
            *p = *p ^ *q;
            *q = *p ^ *q;
            *p = *p ^ *q;
            p++;
            q--;
        }
    }
}