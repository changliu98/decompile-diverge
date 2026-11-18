int stbi__bmp_set_mask_defaults(int *a, int b) {
    if (b == 3) {
        return 1;
    } else if (b == 0) {
        if (a[0] == 16) {
            a[3] = 0x7c00;
            a[4] = 0x3e0;
            a[5] = 0x1f;
        } else if (a[0] == 32) {
            a[3] = 0xff0000;
            a[4] = 0xff00;
            a[5] = 0xff;
            a[6] = 0xff000000;
            a[7] = 0;
        } else {
            a[6] = 0;
            a[5] = 0;
            a[4] = 0;
            a[3] = 0;
        }
        return 1;
    } else {
        return 0;
    }
}