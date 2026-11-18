int sraClipRect2(int *x1, int *y1, int *x2, int *y2, int cx1, int cy1, int cx2, int cy2) {
    if (*x1 < cx1) {
        *x1 = cx1;
    }
    if (*y1 < cy1) {
        *y1 = cy1;
    }
    if (*x1 >= cx2) {
        *x1 = cx2 - 1;
    }
    if (*y1 >= cy2) {
        *y1 = cy2 - 1;
    }
    if (*x2 <= cx1) {
        *x2 = cx1 + 1;
    }
    if (*y2 <= cy1) {
        *y2 = cy1 + 1;
    }
    if (*x2 > cx2) {
        *x2 = cx2;
    }
    if (*y2 > cy2) {
        *y2 = cy2;
    }
    
    if (*x2 > *x1 && *y2 > *y1) {
        return 1;
    }
    return 0;
}