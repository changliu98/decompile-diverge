void sycc420_to_rgb(opj_image_t *img)
{
    unsigned int i, j;
    unsigned int w, h;
    OPJ_INT32 offset, upb;
    OPJ_INT32 *y, *cb, *cr;
    OPJ_INT32 *r, *g, *b;
    OPJ_INT32 *r1, *g1, *b1;
    OPJ_INT32 *r2, *g2, *b2;
    OPJ_INT32 *r3, *g3, *b3;
    OPJ_INT32 *r4, *g4, *b4;

    offset = 1 << (img->comps[0].prec - 1);
    upb = (1 << img->comps[0].prec) - 1;

    w = img->comps[0].w;
    h = img->comps[0].h;

    y = img->comps[0].data;
    cb = img->comps[1].data;
    cr = img->comps[2].data;

    r = (OPJ_INT32*)malloc(w * h * sizeof(OPJ_INT32));
    g = (OPJ_INT32*)malloc(w * h * sizeof(OPJ_INT32));
    b = (OPJ_INT32*)malloc(w * h * sizeof(OPJ_INT32));

    if ((r == NULL) || (g == NULL) || (b == NULL)) {
        if (r) {
            free(r);
        }
        if (g) {
            free(g);
        }
        if (b) {
            free(b);
        }
        return;
    }

    r1 = r;
    g1 = g;
    b1 = b;

    for (i = 0; i < (h & ~1U); i += 2) {
        r2 = r1 + w;
        g2 = g1 + w;
        b2 = b1 + w;
        r3 = r2 + w;
        g3 = g2 + w;
        b3 = b2 + w;
        r4 = r3 + w;
        g4 = g3 + w;
        b4 = b3 + w;

        for (j = 0; j < (w & ~1U); j += 2) {
            sycc_to_rgb(offset, upb, *y, *cb, *cr, r1, g1, b1);
            y++;
            r1++;
            g1++;
            b1++;

            sycc_to_rgb(offset, upb, *y, *cb, *cr, r2, g2, b2);
            y++;
            r2++;
            g2++;
            b2++;

            sycc_to_rgb(offset, upb, *y, *cb, *cr, r3, g3, b3);
            y++;
            r3++;
            g3++;
            b3++;

            sycc_to_rgb(offset, upb, *y, *cb, *cr, r4, g4, b4);
            y++;
            r4++;
            g4++;
            b4++;

            cb++;
            cr++;
        }

        if (j < w) {
            sycc_to_rgb(offset, upb, *y, *cb, *cr, r1, g1, b1);
            y++;
            r1++;
            g1++;
            b1++;

            sycc_to_rgb(offset, upb, *y, *cb, *cr, r2, g2, b2);
            y++;
            r2++;
            g2++;
            b2++;

            cb++;
            cr++;
        }

        r1 += w;
        g1 += w;
        b1 += w;
    }

    if (i < h) {
        for (j = 0; j < (w & ~1U); j += 2) {
            sycc_to_rgb(offset, upb, *y, *cb, *cr, r1, g1, b1);
            y++;
            r1++;
            g1++;
            b1++;

            sycc_to_rgb(offset, upb, *y, *cb, *cr, r2, g2, b2);
            y++;
            r2++;
            g2++;
            b2++;

            cb++;
            cr++;
        }

        if (j < w) {
            sycc_to_rgb(offset, upb, *y, *cb, *cr, r1, g1, b1);
        }
    }

    free(img->comps[0].data);
    img->comps[0].data = r;
    free(img->comps[1].data);
    img->comps[1].data = g;
    free(img->comps[2].data);
    img->comps[2].data = b;

    img->comps[1].w = w;
    img->comps[1].h = h;
    img->comps[2].w = w;
    img->comps[2].h = h;
    img->comps[1].dx = img->comps[0].dx;
    img->comps[2].dx = img->comps[0].dx;
    img->comps[1].dy = img->comps[0].dy;
    img->comps[2].dy = img->comps[0].dy;
}