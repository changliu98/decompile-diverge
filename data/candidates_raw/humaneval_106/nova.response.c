int *func0(int n) {
    int *p = (int *)malloc(n * sizeof(int));
    int i, sum = 0, a = 1, b = 1;
    while (1) {
        if (a <= n) {
            sum += a;
            a = b;
            b = sum;
            if (a % 2 == 0)
                p[a - 1] = b;
            else
                p[a - 1] = sum;
        } else
            break;
    }
    return p;
}