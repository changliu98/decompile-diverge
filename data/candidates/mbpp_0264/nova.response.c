static double func0(int i) {
    if (i < 1)
        exit(1);
    if (i <= 2)
        return 0.25 * i;
    return 0.1 * (i - 2) + 0.5;
}