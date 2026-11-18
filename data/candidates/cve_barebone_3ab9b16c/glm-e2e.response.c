void sycc420_to_rgb(struct image *img) {
    int prec = img->comps[0]->depth;
    int up = 1 << (prec - 1);
    int vp = (1 << prec) - 1;

    int w = img->comps[0]->width;
    int h = img->comps[0]->height;
    int size = w * h;

    int *y = img->comps[0]->data;
    int *cb = img->comps[1]->data;
    int *cr = img->comps[2]->data;

    int *r = malloc(size * sizeof(int));
    int *g = malloc(size * sizeof(int));
    int *b = malloc(size * sizeof(int));

    if (!r || !g || !b) {
        if (r) free(r);
        if (g) free(g);
        if (b) free(b);
        return;
    }

    for (int j = 0; j < (h & ~1); j += 2) {
        int *ny = y + w;
        int *nr = r + w;
        int *ng = g + w;
        int *nb = b + w;

        for (int i = 0; i < (w & ~1); i += 2) {
            sycc_to_rgb(up, vp, *y, *cb, *cr, r, g, b);
            y++; r++; g++; b++;
            sycc_to_rgb(up, vp, *y, *cb, *cr, r, g, b);
            y++; r++; g++; b++;
            sycc_to_rgb(up, vp, *ny, *cb, *cr, nr, ng, nb);
            ny++; nr++; ng++; nb++;
            sycc_to_rgb(up, vp, *ny, *cb, *cr, nr, ng, nb);
            ny++; nr++; ng++; nb++;
            cb++; cr++;
        }

        if (i < w) {
            sycc_to_rgb(up, vp, *y, *cb, *cr, r, g, b);
            y++; r++; g++; b++;
            sycc_to_rgb(up, vp, *ny, *cb, *cr, nr, ng, nb);
            ny++; nr++; ng++; nb++;
            cb++; cr++;
        }

        y += w;
        r += w;
        g += w;
        b += w;
    }

    if (j < h) {
        for (int i = 0; i < (w & ~1); i += 2) {
            sycc_to_rgb(up, vp, *y, *cb, *cr, r, g, b);
            y++; r++; g++; b++;
            sycc_to_rgb(up, vp, *y, *cb, *cr, r, g, b);
            y++; r++; g++; b++;
            cb++; cr++;
        }

        if (i < w) {
            sycc_to_rgb(up, vp, *y, *cb, *cr, r, g, b);
        }
    }

    free(img->comps[0]->data);
    img->comps[0]->data = r;
    free(img->comps[1]->data);
    img->comps[1]->data = g;
    free(img->comps[2]->data);
    img->comps[2]->data = b;

    img->comps[1]->width = w;
    img->comps[1]->height = h;
    img->comps[2]->width = w;
    img->comps[2]->height = h;

    img->comps[1]->stride = img->comps[0]->stride;
    img->comps[2]->stride = img->comps[0]->stride;
    img->comps[1]->depth = img->comps[0]->depth;
    img->comps[2]->depth = img->comps[0]->depth;
}