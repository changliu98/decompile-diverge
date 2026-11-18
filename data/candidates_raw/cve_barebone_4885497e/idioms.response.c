int ras_putdatastd(void *out, struct ras_hdr *hdr, struct jas_image *image, int numcmpts, int *cmpts)
{
    int i; int j; int k; int l; int m; int n; int o; int p; int q;
    struct jas_stream *outp = (jas_stream *)out;
    struct ras_hdr *hdrp = (ras_hdr *)hdr;
    struct jas_image *imagep = (jas_image *)image;
    int numcmptsp = numcmpts;
    int *cmptsp = cmpts;
    struct jas_matrix *data[3];
    for (i = 0; i < numcmptsp; i++) {
        data[i] = (struct jas_matrix *)jas_matrix_new(imagep->brx_-imagep->tlx_, imagep->bry_-imagep->tly_);
        if (data[i] == ((void *)0)) {
            __jas_seterr(("data[i]", "/work/harness.c", 246, "int ras_putdatastd(jas_stream_t *, ras_hdr_t *, jas_image_t *, int, int *)"));
        }
    }
    int rowsize = (hdrp->depth * hdrp->width + 15)/16 * 2;
    int pad = rowsize - (hdrp->depth * hdrp->width + 7)/8;
    hdrp->length = (hdrp->height * rowsize);
    for (i = 0; i < hdrp->height; i++) {
        for (j = 0; j < numcmptsp; j++) {
            if (ras_getdata(imagep, cmptsp[j], ((void *)0), i, imagep->brx_-imagep->tlx_, 1, data[j]) == -1) {
                return -1;
            }
        }
        unsigned int z = 0;
        int nz = 0;
        for (j = 0; j < hdrp->width; j++) {
            z = z << hdrp->depth;
            if (hdrp->depth == 24 || hdrp->depth == 32) {
                struct jas_seqent v1; struct jas_seqent v2; struct jas_seqent v3;
                if (data[0]->numrows_ == 1) {
                    v1 = (data[0]->rows_[0][j]);
                }
                else {
                    v1 = (data[0]->rows_[j][0]);
                }
                if (data[1]->numrows_ == 1) {
                    v2 = (data[1]->rows_[0][j]);
                }
                else {
                    v2 = (data[1]->rows_[j][0]);
                }
                if (data[2]->numrows_ == 1) {
                    v3 = (data[2]->rows_[0][j]);
                }
                else {
                    v3 = (data[2]->rows_[j][0]);
                }
                int v = (v1 & 0xff) | ((v2 & 0xff) << 8) | ((v3 & 0xff) << 16);
                if (hdrp->depth == 32) {
                    struct jas_seqent v4 = (0xffffffff);
                    z = z | (v & v4);
                }
                else {
                    struct jas_seqent v4 = ((1 << hdrp->depth)-1);
                    z = z | (v & v4);
                }
            }
            else {
                struct jas_seqent v1;
                if (data[0]->numrows_ == 1) {
                    v1 = (data[0]->rows_[0][j]);
                }
                else {
                    v1 = (data[0]->rows_[j][0]);
                }
                int v = (v1 & 0xff);
                if (hdrp->depth == 32) {
                    struct jas_seqent v2 = (0xffffffff);
                    z = z | (v & v2);
                }
                else {
                    struct jas_seqent v2 = ((1 << hdrp->depth)-1);
                    z = z | (v & v2);
                }
            }
            nz = nz + hdrp->depth;
            while (nz >= 8) {
                int c = (z >> (nz-8)) & 0xff;
                if (ras_putdata(outp, c) == -1) {
                    return -1;
                }
                nz = nz - 8;
                if (nz == 32) {
                    struct jas_seqent v = (0xffffffff);
                    z = z & v;
                }
                else {
                    struct jas_seqent v = ((1 << nz)-1);
                    z = z & v;
                }
            }
        }
        if (nz > 0) {
            int c = (z >> (8-nz)) & ((1 << nz)-1);
            if (ras_putdata(outp, c) == -1) {
                return -1;
            }
        }
        if (pad % 2 == 1) {
            if (ras_putdata(outp, 0) == -1) {
                return -1;
            }
        }
    }
    for (i = 0; i < numcmptsp; i++) {
        jas_matrix_free(data[i]);
    }
    return 0;
}