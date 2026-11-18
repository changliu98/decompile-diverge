int pmc_overflow(int x) {
    int r;
    if (x < 0)
        r = 1;
    else
        r = 0;
    return r;
}