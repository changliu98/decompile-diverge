void copy_dice(int *dest, const int *src) {
    for (int i = 0; i < 6; i++) {
        dest[i] = src[i];
    }
}