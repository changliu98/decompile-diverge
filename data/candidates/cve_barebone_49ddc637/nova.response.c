void jpc_qmfb_split_colgrp(uint8_t *frame, int width, int height, int stride) {
    int i, j, k;
    int width_blocks = (width + 2) / 2 - 1;
    uint8_t *p, *q;
    uint8_t *tmp = (uint8_t *)malloc(width_blocks * 8 * sizeof(uint8_t));
    if (tmp == NULL)
        abort();
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 16; j++) {
            p = frame + i * stride * height + j * width;
            q = tmp + j * width;
            for (k = 0; k < width_blocks; k++) {
                *q = *p;
                q += 8;
                p += 2 * width;
            }
        }
        frame += width * height * (1 - i) * 2;
    }
    free(tmp);
}