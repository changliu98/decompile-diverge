int func0(int *p1, float *p2, char *p3) {
    *p1 = *p1 + 1;
    *p2 = *p2 + 2222.22;
    *p3 = *p3 + 4;
    return **p1;
}