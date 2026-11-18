int imagetopnm(opj_image_t *image, char *outfile, int force_split)
{
    FILE *fdest;
    char *destname;
    char *tt;
    int i, j, k, w, h, max, len, hr, wr, triple, has_alpha, want_gray, two,
        fails, adjustR, adjustG, adjustB, adjustA, prec, ncomp;
    OPJ_INT32 *red, *green, *blue, *alpha;

    if (image->comps[0].prec > 16) {
        fprintf(stderr, "%s:%d:imagetopnm\n\tprecision %d is larger than 16\n\t: refused.\n", "/work/harness.c", 161, image->comps[0].prec);
        return 1;
    }

    tt = outfile;
    while (*tt)
        tt++;
    tt -= 2;
    if (*tt == 'g' || *tt == 'G') {
        ncomp =