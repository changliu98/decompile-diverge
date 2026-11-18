static void drwav_f64_to_s16(short *out, double *in, unsigned long len)
{
    unsigned long i;
    double v;
    double s;
    int outv;

    for (i = 0; i < len; i++) {
        v = in[i];
        if (v > (double)((1 << 15) - 1))
            s = (double)((1 << 15) - 1);
        else if (v < (double)(-(1 << 15)))
            s = (double)(-(1 << 15));
        else
            s = v;
        outv = (int)(s + (((s < 0) ^ (v < 0))? -0.5 : 0.5));
        outv = (outv - (1 << 15)) << 1;
        out[i] = outv;
    }
}