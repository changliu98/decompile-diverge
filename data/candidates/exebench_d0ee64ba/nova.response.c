void simplify(int *a, int *b) {
    int t, a1, b1;
    if (*a < *b && *a > 0)
        t = *a;
    else if (*b > 0)
        t = *b;
    else
        t = *a;
    while (t!= 0) {
        if (*a % t == 0 && *b % t == 0) {
            a1 = t;
            t = 0;
        } else if (t > 0)
            t--;
        else
            t++;
    }
    if (a1 == -1)
        a1 = a1 * a1;
    *a = *a / a1;
    *b = *b / a1;
}