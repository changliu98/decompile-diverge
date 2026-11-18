void j2gcal(int *y, int *m, int *d, double j) {
    int lyear = (int)(j + 0.5) + 68569;
    int cycle = lyear / 146097;
    lyear -= ((cycle * 146097 + 3) / 4);
    int yday = (lyear + 1) * 4000 / 1461001;
    lyear -= (yday * 1461 / 4 - 31);
    int mday = lyear / 80;
    *d = lyear - mday * 80;
    int mon = mday / 11;
    *m = mday + 2 - mon * 12;
    *y = 100 * (cycle - 49) + yday + mon;
}