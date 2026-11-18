void wmv2_idct_row_mmi(short *block)
{
    int a0, a1, a2, a3, a4, a5, a6, a7;
    int b0, b1, b2, b3, b4, b5, b6, b7;
    int c0, c1, c2, c3, c4, c5, c6, c7;
    int d0, d1, d2, d3, d4, d5, d6, d7;
    int e0, e1, e2, e3, e4, e5, e6, e7;
    int f0, f1, f2, f3, f4, f5, f6, f7;
    int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;

    a0 = block[0] * W0 + block[4] * W0;
    a1 = block[1] * W1 + block[7] * W7;
    a2 = block[2] * W2 + block[6] * W6;
    a3 = block[3] * W3 + block[5] * W5;
    a4 = block[0] * W0 - block[4] * W0;
    a5 = block[1] * W1 - block[7] * W7;
    a6 = block[2] * W2 - block[6] * W6;
    a7 = block[3] * W3 - block[5] * W5;

    b0 = a0 + a2 + a1 + a3;
    b1 = a4 + a6 + a5 + a7;
    b2 = a4 - a6 - a5 - a7;
    b3 = a0 - a2 + a1 + a3;
    b4 = a0 - a2 - a1 - a3;
    b5 = a4 - a6 + a5 - a7;
    b6 = a4 + a6 - a5 - a7;
    b7 = a0 + a2 - a1 - a3;

    c0 = b0 + b1;
    c1 = b2 + b3;
    c2 = b2 - b3;
    c3 = b0 - b1;
    c4 = b4 - b5;
    c5 = b4 - b5 + b6 - b7;
    c6 = b4 + b5 - b6 - b7;
    c7 = b4 + b5 + b6 + b7;

    d0 = c0 + c3;
    d1 = c1 + c2;
    d2 = c1 - c2;
    d3 = c0 - c3;
    d4 = c4 - c5;
    d5 = c4 - c5 + c6 - c7;
    d6 = c4 + c5 - c6 - c7;
    d7 = c4 + c5 + c6 + c7;

    e0 = (d0 + d1) >> 8;
    e1 = (d0 - d1) >> 8;
    e2 = (d2 + d3) >> 8;
    e3 = (d2 - d3) >> 8;
    e4 = (d4 + d5) >> 8;
    e5 = (d4 - d5) >> 8;
    e6 = (d6 + d7) >> 8;
    e7 = (d6 - d7) >> 8;

    block[0] = e0;
    block[1] = e1;
    block[2] = e2;
    block[3] = e3;
    block[4] = e4;
    block[5] = e5;
    block[6] = e6;
    block[7] = e7;
}