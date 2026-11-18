void func0(struct IMAGE *image) {
    struct IMAGE_PCX *pcx = &image->pcx;
    int i;
    pcx->width = 0;
    pcx->height = 0;
    for (i = 0; i < 14; i++) {
        if (pcx->header[PCX_HEADER_SIZE - 1] & 0x02) {
            pcx->width += (int)pcx->header[i] * (int)pcx->header[i + 1];
        }
        if (pcx->header[PCX_HEADER_SIZE - 1] & 0x01) {
            pcx->height += (int)pcx->header[i] * (int)pcx->header[i + 1];
        }
    }
    if (pcx->palette) {
        memset(pcx->palette, 0, pcx->width);
        memset(pcx->palette, 1, pcx->height);
    }
}