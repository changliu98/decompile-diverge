void color_cmyk_to_rgb(opj_image_t *image)
{
    OPJ_UINT32 i;
    OPJ_UINT32 width, height;
    OPJ_FLOAT32 *c, *m, *y, *k, *r, *g, *b;
    OPJ_FLOAT32 fc, fm, fy, fk, fr, fg, fb;
    OPJ_FLOAT32 coef_c, coef_m, coef_y, coef_k;

    width = image->comps[0].w;
    height = image->comps[0].h;

    if (image->numcomps < 4) {
        return;
    }

    coef_c = 1.0f / (float)((1 << image->comps[0].prec) - 1);
    coef_m = 1.0f / (float)((1 << image->comps[1].prec) - 1);
    coef_y = 1.0f / (float)((1 << image->comps[2].prec) - 1);
    coef_k = 1.0f / (float)((1 << image->comps[3].prec) - 1);

    c = (OPJ_FLOAT32*)image->comps[0].data;
    m = (OPJ_FLOAT32*)image->comps[1].data;
    y = (OPJ_FLOAT32*)image->comps[2].data;
    k = (OPJ_FLOAT32*)image->comps[3].data;

    r = (OPJ_FLOAT32*)image->comps[0].data;
    g = (OPJ_FLOAT32*)image->comps[1].data;
    b = (OPJ_FLOAT32*)image->comps[2].data;

    for (i = 0; i < width * height; i++) {
        fc = *c++ * coef_c;
        fm = *m++ * coef_m;
        fy = *y++ * coef_y;
        fk = *k++ * coef_k;

        fr = 1.0f - (fc * (1.0f - fk) + fk);
        fg = 1.0f - (fm * (1.0f - fk) + fk);
        fb = 1.0f - (fy * (1.0f - fk) + fk);

        *r++ = (OPJ_INT32)(fr * 255.0f);
        *g++ = (OPJ_INT32)(fg * 255.0f);
        *b++ = (OPJ_INT32)(fb * 255.0f);
    }

    free(image->comps[3].data);
    image->comps[3].data = NULL;
    image->comps[0].prec = 8;
    image->comps[1].prec = 8;
    image->comps[2].prec = 8;
    image->numcomps--;
    image->color_space = OPJ_CLRSPC_SRGB;

    for (i = 3; i < image->numcomps; i++) {
        memcpy(&image->comps[i], &image->comps[i + 1], sizeof(opj_image_comp_t));
    }
}