static int clip_img(int x, int y, int w, int h, int *x1, int *y1, int *x2, int *y2, int *x3, int *y3) {
    int ret;

    if (*x1 > x) {
        *x1 -= x;
        *x2 += x - *x1;
        *x3 += x - *x1;
        *x1 = x;
    }
    if (*y1 > y) {
        *y1 -= y;
        *y2 += y - *y1;
        *y3 += y - *y1;
        *y1 = y;
    }
    if (*x2 > w) {
        *x2 -= w;
    }
    if (*y2 > h) {
        *y2 -= h;
    }

    ret = (*x1 >= 0) && (*y1 >= 0) && (*x2 >= 0) && (*y2 >= 0) && (*x3 >= 0) && (*y3 >= 0);

    return ret & 1;
}