void func0(char *str) {
    char *p1, *p2, c;
    for (p1 = str, p2 = str + strlen(str) - 1; p1 < p2; p1++, p2--) {
        c = *p1;
        *p1 = *p2;
        *p2 = c;
    }
}