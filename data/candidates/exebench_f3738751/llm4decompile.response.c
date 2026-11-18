int foo(int *p) {
    int i;
    int j;
    i = 0;
    j = 0;
    p[i] = j;
    return j;
}