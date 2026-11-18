void zywrle_calc_size(int *w, int *h, int level) {
    int mask = ~((1 << level) - 1);
    *w &= mask;
    *h &= mask;
}