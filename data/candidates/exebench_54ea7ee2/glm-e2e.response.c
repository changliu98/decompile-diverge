void BTIC2D_TransWHT_Vert8(int *src, int *dst) {
    int v0 = src[0];
    int v1 = src[8];
    int v2 = src[16];
    int v3 = src[24];
    int v4 = src[32];
    int v5 = src[40];
    int v6 = src[48];
    int v7 = src[56];

    int s0 = v0 + v4;
    int s1 = v1 + v5;
    int s2 = v2 + v6;
    int s3 = v3 + v7;

    int t0 = (s0 >> 1) - v4;
    int t1 = (s1 >> 1) - v5;
    int t2 = (s2 >> 1) - v6;
    int t3 = (s3 >> 1) - v7;

    int u0 = s0 + s2;
    int u1 = s1 + s3;
    int u2 = (u0 >> 1) - s2;
    int u3 = (u1 >> 1) - s3;

    int w0 = t0 + t2;
    int w1 = t1 + t3;
    int w2 = (w0 >> 1) - t2;
    int w3 = (w1 >> 1) - t3;

    int x0 = u0 + u1;
    int x1 = (x0 >> 1) - u1;
    int x2 = u2 + u3;
    int x3 = (x2 >> 1) - u3;
    int x4 = w0 + w1;
    int x5 = (x4 >> 1) - w1;
    int x6 = w2 + w3;
    int x7 = (x6 >> 1) - w3;

    dst[0]  = x0;
    dst[8]  = x4;
    dst[16] = x6;
    dst[24] = x2;
    dst[32] = x3;
    dst[40] = x7;
    dst[48] = x5;
    dst[56] = x1;
}