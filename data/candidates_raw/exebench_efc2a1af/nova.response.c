void func0(int h, int m, int h1, int *m1, int *h2, int *m2) {
    int hh, mm;
    if (m < h1)
        hh = h1;
    else
        hh = h;
    if (hh > m)
        mm = m;
    else
        mm = h;
    while (1) {
        *h2 = (hh + mm) / 20;
        if (hh == mm) {
            *m1 = 0;
            *m2 = 0;
            break;
        }
        if (*h2 < 50) {
            *m1 = (mm - hh) * 100 / (mm + hh);
            break;
        } else {
            *m1 = (mm - hh) * 100 / (2000 - mm - hh);
            break;
        }
    }
    if (h == h1)
        hh = 120 + (m - h1) * 60 / (h - h1);
    if (h == m)
        hh = 240 + (h1 - m) * 60 / (h - m);
    if (h!= m)
        hh = (hh % 360);
    *m2 = hh;
}