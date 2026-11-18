int obdRevConvert_04(int *p, int *q, float u, float v, float w) {
    *p = (int)(u * 1000 / 3);
    return 1;
}