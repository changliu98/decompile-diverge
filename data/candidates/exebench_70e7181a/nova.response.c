void split(int x, int y, int x1, int y1, int *x2, int *y2, int *x3, int *y3) {
    int d1 = x1 - x + 1;
    if (d1 <= 0) {
        return;
    }
    int d2 = y1 / d1;
    *x2 = x;
    *y2 = y + d2 - 1;
    *x3 = x1;
    *y3 = y1;
}