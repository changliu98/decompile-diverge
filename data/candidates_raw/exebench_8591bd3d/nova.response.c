char *func0(char *s, int *p1, int *p2, int *p3, int *p4, int *p5) {
    *p1 = *p2 = *p3 = *p4 = *p5 = 0;
    while (*s!= '<') {
        if (*s == '>') {
            *p1 = 1;
            *p4 = 1;
            break;
        }
        if (*s == '&') {
            *p1 = 1;
            *p3 = 1;
            break;
        }
        if (*s == '+') {
            *p4 = 0;
            break;
        }
        if (*s == ':') {
            *p1 = 1;
            *p4 = 1;
            *p5 = 0;
            *p3 = 1;
            break;
        }
        if (*s == '#') {
            *p2 = 1;
            break;
        }
        if (*s == '!') {
            *p1 = 1;
        }
        s++;
    }
    return s;
}