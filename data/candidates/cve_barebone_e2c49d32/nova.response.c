int _gd2GetHeader(FILE *fp, int *x, int *y, int *comp, int *type, int *planes,
         int *bpp) {
    int i, j, k, l, m, n;
    char buf[1024];
    unsigned char *data;

    for (i = 0;;) {
        if (i < 5) {
            if ((j = getc(fp)) == EOF)
                break;
            buf[i++] = j;
        } else {
            if (strncmp(buf, "BM", 2)!= 0 || *planes!= 1 || *bpp!= 8 ||
                *planes!= 1 || *bpp!= 8)
                break;
            l = *x * *y;
            if (l <= 0 || l > sizeof(buf))
                break;
            data = (unsigned char *)calloc(l, sizeof(unsigned char));
            if (data == NULL)
                break;
            for (i = 0; i < l; i++) {
                if (getc(fp)!= 1)
                    break;
                if (getc(fp)!= 1)
                    break;
                if (data[i] < 0 || data[i] > 1)
                    break;
            }
            *planes = data;
            return 1;
        }
    }
    return 0;
}