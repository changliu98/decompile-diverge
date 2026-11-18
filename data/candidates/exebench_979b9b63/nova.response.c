int openI2CBus(int *a, char *s) {
    int res;
    *a = atoi(s);
    if (*a < 0)
        res = 1;
    else
        res = 0;
    return res;
}