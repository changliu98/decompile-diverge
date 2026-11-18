void advance_spos(int *x) {
    int i;
    for (i = 0; i < 5; i++)
        x[i] = (x[i] + 1) % (i + 43);
}