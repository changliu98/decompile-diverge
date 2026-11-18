void func0(char *str) {
    char *p1 = str, *p2 = str;
    char tmp;
    while (*p1++)
        ;
    p1--;
    while (p1 > p2) {
        tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1--;
        p2++;
    }
}