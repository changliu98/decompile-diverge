int *func0(int n) {
    int *p = (int *)malloc(n * sizeof(int));
    p[0] = n;
    int i = 1;
    while (1) {
        if (p[i - 1] < n) {
            p[i] = p[i - 1] + 2;
            i++;
        } else {
            break;
        }
    }
    return p;
}