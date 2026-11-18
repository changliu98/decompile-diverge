void pos2ddd(long pos_x, long pos_y, double *out_x, double *out_y) {
    // 0x927c0 = 600000
    *out_x = (double)(pos_x % 600000);
    *out_y = (double)(pos_y % 600000);

    // The constant at 0x2008 is 0.5
    *out_x = *out_x + ((double)pos_x + fabs(*out_x) * 0.5) / 0.5;
    *out_y = *out_y + ((double)pos_y + fabs(*out_y) * 0.5) / 0.5;
}