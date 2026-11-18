void deblock_ver_luma(short *input, short *mb_dqcoeff)
{
    int i;
    short *in = (short *)input;
    short *in1 = (short *)input;
    short *out = (short *)input;
    short *out1 = (short *)input;
    for (i = 0; i < 4; i++)
    {
        int a = in1[12] + in1[ 0];
        int b = in1[ 8] + in1[ 4];
        int c = in1[ 4] - in1[ 8];
        int d = in1[ 0] - in1[12];
        out[ 0] = a + b;
        out[ 4] = c + d;
        out[ 8] = a - b;
        out[12] = c - d;
        in1++;
        out++;
    }
    in1 = out;
    out = (short *)out1;
    for (i = 0; i < 4; i++)
    {
        int a = in1[ 3] + in1[ 0];
        int b = in1[ 2] + in1[ 1];
        int c = in1[ 1] - in1[ 2];
        int d = in1[ 0] - in1[ 3];
        out[ 0] = (a + b + 3)/4;
        out[ 1] = (c + d + 3)/4;
        out[ 2] = (a - b + 3)/4;
        out[ 3] = (c - d + 3)/4;
        in1 += 4;
        out += 4;
    }
    for (i = 0; i < 16; i++)
    {
        mb_dqcoeff[i*16 + 0] = out[i*4 + 0];
    }
}