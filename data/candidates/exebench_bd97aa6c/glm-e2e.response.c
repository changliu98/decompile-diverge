void subpixels(unsigned int pixel, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d) {
    *a = (pixel >> 24) & 0xFF;
    *b = (pixel >> 16) & 0xFF;
    *c = (pixel >> 8) & 0xFF;
    *d = (pixel >> 0) & 0xFF;
}