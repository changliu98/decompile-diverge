void stbi__idct_block(unsigned char *out, int out_stride, short *data) {
    int i;
    int val[64]; // Allocated on stack at -0x120(%rbp)
    int *p = val;
    short *d = data;

    // 1st pass: process rows
    for (i = 0; i < 8; i++) {
        // Fast path: if all AC coefficients are zero
        if (d[1] == 0 && d[2] == 0 && d[3] == 0 && d[4] == 0 && 
            d[5] == 0 && d[6] == 0 && d[7] == 0) {
            int v = d[0] << 3; // Equivalent to d[0] << 4 >> 1
            p[0] = v; p[1] = v; p[2] = v; p[3] = v;
            p[4] = v; p[5] = v; p[6] = v; p[7] = v;
        } else {
            int t0 = d[0], t1 = d[2], t2 = d[4], t3 = d[6];
            int t4 = d[1], t5 = d[3], t6 = d[5], t7 = d[7];

            int p = t0 + t2;
            int q = t0 - t2;
            int r = t1 + t3;
            int s = t1 - t3;

            int x0 = stbi__fsh(p + r);
            int x1 = stbi__fsh(p - r);
            int x2 = stbi__fsh(q + s);
            int x3 = stbi__fsh(q - s);

            int p1 = stbi__MUL16(t4 + t7, stbi__f2f(0.5411961f));
            int p2 = stbi__MUL16(t4 - t7, stbi__f2f(0.5411961f));
            int p3 = stbi__MUL16(t5 + t6, stbi__f2f(0.5411961f));
            int p4 = stbi__MUL16(t5 - t6, stbi__f2f(0.5411961f));

            int p5 = p1 + p4;
            int p6 = p2 + p3;
            int p7 = p1 + p3;
            int p8 = p2 + p4;

            int p9  = stbi__MUL16(p5 + p6, stbi__f2f(1.175875602f));
            int p10 = stbi__MUL16(p5, stbi__f2f(0.899976223f));
            int p11 = stbi__MUL16(p6, stbi__f2f(2.562915447f));
            int p12 = stbi__MUL16(p7, stbi__f2f(0.298631336f));
            int p13 = stbi__MUL16(p8, stbi__f2f(2.053119869f));

            p5 = p9 + stbi__MUL16(p7, stbi__f2f(-3.072711026f));
            p6 = p9 + stbi__MUL16(p8, stbi__f2f(-1.847759065f));
            p7 = stbi__MUL16(p7, stbi__f2f(-2.562915447f));
            p8 = stbi__MUL16(p8, stbi__f2f(-0.899976223f));

            p5 += p13;
            p6 += p12;
            p7 += p11;
            p8 += p10;

            x0 += 512;
            x1 += 512;
            x2 += 512;
            x3 += 512;

            p[0] = (x0 + p5) >> 10;
            p[7] = (x0 - p5) >> 10;
            p[1] = (x1 + p6) >> 10;
            p[6] = (x1 - p6) >> 10;
            p[2] = (x2 + p7) >> 10;
            p[5] = (x2 - p7) >> 10;
            p[3] = (x3 + p8) >> 10;
            p[4] = (x3 - p8) >> 10;
        }
        p += 8;
        d += 8;
    }

    // 2nd pass: process columns
    p = val;
    unsigned char *o = out;
    for (i = 0; i < 8; i++) {
        int t0 = p[0], t1 = p[8], t2 = p[16], t3 = p[24];
        int t4 = p[32], t5 = p[40], t6 = p[48], t7 = p[56];

        int p_val = t0 + t2;
        int q = t0 - t2;
        int r = t1 + t3;
        int s = t1 - t3;

        int x0 = stbi__fsh(p_val + r);
        int x1 = stbi__fsh(p_val - r);
        int x2 = stbi__fsh(q + s);
        int x3 = stbi__fsh(q - s);

        int p1 = stbi__MUL16(t4 + t7, stbi__f2f(0.5411961f));
        int p2 = stbi__MUL16(t4 - t7, stbi__f2f(0.5411961f));
        int p3 = stbi__MUL16(t5 + t6, stbi__f2f(0.5411961f));
        int p4 = stbi__MUL16(t5 - t6, stbi__f2f(0.5411961f));

        int p5 = p1 + p4;
        int p6 = p2 + p3;
        int p7 = p1 + p3;
        int p8 = p2 + p4;

        int p9  = stbi__MUL16(p5 + p6, stbi__f2f(1.175875602f));
        int p10 = stbi__MUL16(p5, stbi__f2f(0.899976223f));
        int p11 = stbi__MUL16(p6, stbi__f2f(2.562915447f));
        int p12 = stbi__MUL16(p7, stbi__f2f(0.298631336f));
        int p13 = stbi__MUL16(p8, stbi__f2f(2.053119869f));

        p5 = p9 + stbi__MUL16(p7, stbi__f2f(-3.072711026f));
        p6 = p9 + stbi__MUL16(p8, stbi__f2f(-1.847759065f));
        p7 = stbi__MUL16(p7, stbi__f2f(-2.562915447f));
        p8 = stbi__MUL16(p8, stbi__f2f(-0.899976223f));

        p5 += p13;
        p6 += p12;
        p7 += p11;
        p8 += p10;

        // 0x1010000 is equivalent to 512 << 13
        x0 += 0x1010000;
        x1 += 0x1010000;
        x2 += 0x1010000;
        x3 += 0x1010000;

        o[0] = stbi__clamp((x0 + p5) >> 17);
        o[7] = stbi__clamp((x0 - p5) >> 17);
        o[1] = stbi__clamp((x1 + p6) >> 17);
        o[6] = stbi__clamp((x1 - p6) >> 17);
        o[2] = stbi__clamp((x2 + p7) >> 17);
        o[5] = stbi__clamp((x2 - p7) >> 17);
        o[3] = stbi__clamp((x3 + p8) >> 17);
        o[4] = stbi__clamp((x3 - p8) >> 17);

        p++;
        o += out_stride;
    }
}