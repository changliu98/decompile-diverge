int obdRevConvert_2C(int *p, int *q, float u, float v, float w) {
    *p = (int)((3598 - 3590 * u) / (1500 * v));
    return 1;
}