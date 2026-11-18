void __cdecl vp8_short_inv_walsh4x4_simd(short *input, short *mb_dqcoeff)
{
    short output[16];
    short *op;
    int i;

    // First pass: Horizontal 1D Hadamard transform
    op = output;
    for (i = 0; i < 4; ++i)
    {
        short a1 = input[12] + input[0];
        short b1 = input[8]  + input[4];
        short c1 = input[4]  - input[8];
        short d1 = input[0]  - input[12];

        op[0]  = b1 + a1;
        op[4]  = d1 + c1;
        op[8]  = a1 - b1;
        op[12] = d1 - c1;

        input++;
        op++;
    }

    // Second pass: Vertical 1D Hadamard transform with rounding and scaling
    op = output;
    for (i = 0; i < 4; ++i)
    {
        int a1 = op[3] + op[0];
        int b1 = op[2] + op[1];
        int c1 = op[1] - op[2];
        int d1 = op[0] - op[3];

        op[0] = (b1 + a1 + 3) >> 3;
        op[1] = (d1 + c1 + 3) >> 3;
        op[2] = (a1 - b1 + 3) >> 3;
        op[3] = (d1 - c1 + 3) >> 3;

        op += 4;
    }

    // Store the 4x4 block into mb_dqcoeff with a stride of 16
    for (i = 0; i < 16; ++i)
        mb_dqcoeff[16 * i] = output[i];
}