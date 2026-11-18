int alphabeta_cutoff(int a, int *max, int *min, int flag) {
    int r;
    if (flag && a > *max)
        *max = a;
    else if (!flag && a < *min)
        *min = a;
    if (*min <= *max)
        r = 1;
    else
        r = 0;
    return r;
}