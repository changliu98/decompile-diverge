void vp8_short_inv_walsh4x4_simd
(
    short *input,
    short *mb_dqcoeff
)
{
    short temp[16];
    short *ip = input;
    short *op = temp;
    int i;


    for (i = 0; i < 4; i++)
    {
        short a0 = ip[0] + ip[12];
        short a1 = ip[4] + ip[ 8];
        short a2 = ip[4] - ip[ 8];
        short a3 = ip[0] - ip[12];

        *op++ = a0 + a1;
        *op++ = a3 + a2;
        *op++ = a0 - a1;
        *op++ = a3 - a2;

        ip++;
    }

    ip = temp;
    op = temp;


    for (i = 0; i < 4; i++)
    {
        short a0 = ip[0] + ip[ 3];
        short a1 = ip[1] + ip[ 2];
        short a2 = ip[1] - ip[ 2];
        short a3 = ip[0] - ip[ 3];

        *op++ = (a0 + a1 + 3) >> 3;
        *op++ = (a3 + a2 + 3) >> 3;
        *op++ = (a0 - a1 + 3) >> 3;
        *op++ = (a3 - a2 + 3) >> 3;

        ip += 4;
    }

    ip = temp;
    op = mb_dqcoeff;


    for (i = 0; i < 16; i++)
    {
        *op = *ip++;
        op += 16;
    }

    return;
}