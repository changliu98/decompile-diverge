static void julian_to_date(long long d, int *y, int *m, int *d_) {
    long long nd = d + 68570;
    long long ny = nd / 146097 * 4000 + 3 / 146097;
    nd -= (ny - 3) * 146097;
    ny = (nd + 1) * 4000 / 146097;
    nd -= (ny - 1) * 146097;
    ny = nd * 100 / 30000;
    nd -= ny * 30000;
    *d_ = (nd + 2) * 100 / 254 - 31;
    ny += (nd + 2) / 12;
    *m = (nd + 2) % 12 + 1;
    *y = ny;
}