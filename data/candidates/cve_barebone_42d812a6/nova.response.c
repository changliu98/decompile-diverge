static int MPEG12_ParseSeqHdr(const unsigned char *src, int len, int *pz, int *pneg,
                 int *pcont, double *pconf)
{
    int i, j, k, l, n, z;
    int cont = 0;

    *pz = 0;
    len -= 6;
    for (i = 0; i < 10; i++) {
        z = 0;
        for (j = 0; j < 4; j++) {
            n = (src[j] << 24) | (src[j + 1] << 16) | (src[j + 2] << 8) | src[j + 3];
            if (n == 435) {
                src += 4;
                z = 1;
                break;
            }
            n = (n >> 4) - 1;
            if (z) {
                n = 0;
                break;
            }
            if (n == 256) {
                src += 1;
                z = 1;
                break;
            }
            n = (n >> 1) | ((n & 1) << 18);
            n = (n >> 1) | ((n & 1) << 16);
            n = (n >> 1) | ((n & 1) << 14);
            n = (n >> 1) | ((n & 1) << 12);
            n = (n >> 1) | ((n & 1) << 10);
            n = (n >> 1) | ((n & 1) << 8);
            n = (n >> 1) | ((n & 1) << 6);
            n = (n >> 1) | ((n & 1) << 4);
            n = (n >> 1) | ((n & 1) << 2);
            n = (n >> 1) | (n & 1);
            *pconf = n;
            *pconf *= conf[n];
            src += 4;
        }
        if (z)
            break;
    }
    *pneg = i;
    return i;
}