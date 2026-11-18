int imagetopnm(opj_image_t * img, char *filename)
{
    FILE *src = NULL;
    int compno, prec, max, ncomp, i, adjustR, adjustG, adjustB, adjustA;
    int two, triple, has_alpha, fails;
    int wr, hr;
    int *red, *green, *blue, *alpha;
    int alpha_value;
    char *filename2;
    size_t l, dotpos;

    if ((prec = img->comps[0].prec) > 16) {
        fprintf(stderr, "%s:%d