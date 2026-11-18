int ras_putdatastd(struct jas_stream *out, struct ras_hdr *hdr, struct ras_image_data *data, int numcmpts, int *cmpts) {
    struct jas_matrix *matrix[4];
    int i;
    int j;
    int k;
    int v;
    int depth;
    int pad_mask;
    int numbytes;
    int bias;
    int bit_offset;
    int pixel;
    int c;
    int mask;
    int nz;
    long val;
    long r;
    long g;
    long b;
    long a;

    for (i = 0; i < numcmpts; ++i) {
        matrix[i] = (struct jas_matrix *)jas_matrix_create(data->height - data->y_offset, data->width - data->x_offset);
        assert(matrix[i]);
    }

    numbytes = ((hdr->width * hdr->depth + 15) / 16) * 2;
    bias = numbytes - ((hdr->width * hdr->depth + 7) / 8);
    hdr->length = numbytes * hdr->height;

    for (j = 0; j < hdr->height; ++j) {
        for (i = 0; i < numcmpts; ++i) {
            if (jas_image_readcmpt(data, cmpts[i], data->x_offset, j, data->width - data->x_offset, 1, matrix[i])) {
                return -1;
            }
        }

        pixel = 0;
        bit_offset = 0;
        for (k = 0; k < hdr->width; ++k) {
            pixel <<= hdr->depth;

            if (hdr->depth == 24 || hdr->depth == 32) {
                struct jas_matrix_internal *mat0 = (struct jas_matrix_internal *)matrix[0];
                struct jas_matrix_internal *mat1 = (struct jas_matrix_internal *)matrix[1];
                struct jas_matrix_internal *mat2 = (struct jas_matrix_internal *)matrix[2];

                if (mat0->numrows == 1) {
                    r = mat0->rows[0][k];
                } else {
                    r = mat0->rows[k][0];
                }

                if (mat1->numrows == 1) {
                    g = mat1->rows[0][k];
                } else {
                    g = mat1->rows[k][0];
                }

                if (mat2->numrows == 1) {
                    b = mat2->rows[0][k];
                } else {
                    b = mat2->rows[k][0];
                }

                v = (r & 0xff) | ((g & 0xff) << 8) | ((b & 0xff) << 16);
            } else {
                struct jas_matrix_internal *mat0 = (struct jas_matrix_internal *)matrix[0];
                if (mat0->numrows == 1) {
                    val = mat0->rows[0][k];
                } else {
                    val = mat0->rows[k][0];
                }
                v = (int)val;
            }

            if (hdr->depth == 32) {
                mask = 0xffffffff;
            } else {
                mask = (1 << hdr->depth) - 1;
            }

            pixel |= (v & mask);
            bit_offset += hdr->depth;

            while (bit_offset >= 8) {
                c = (pixel >> (bit_offset - 8)) & 0xff;
                if (jas_stream_putc(out, c) == -1) {
                    return -1;
                }
                bit_offset -= 8;
                if (bit_offset == 32) {
                    pad_mask = 0xffffffff;
                } else {
                    pad_mask = (1 << bit_offset) - 1;
                }
                pixel &= pad_mask;
            }
        }

        if (bit_offset > 0) {
            c = (pixel >> (8 - bit_offset)) & ((1 << bit_offset) - 1);
            if (jas_stream_putc(out, c) == -1) {
                return -1;
            }
        }

        if (bias % 2 != 0) {
            if (jas_stream_putc(out, 0) == -1) {
                return -1;
            }
        }
    }

    for (i = 0; i < numcmpts; ++i) {
        jas_matrix_destroy(matrix[i]);
    }

    return 0;
}