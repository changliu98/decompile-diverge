void __cdecl wmv2_idct_row_mmi(short *b)
{
    int a0, a1, a2, a3, a4, a5, a6, a7;
    int s1, s2;

    // Intermediate calculations using IDCT constants (W0, W1, etc.)
    a0 = b[4] * W0 + b[0] * W0;
    a1 = b[7] * W7 + b[1] * W1;
    a2 = b[6] * W6 + b[2] * W2;
    a3 = b[5] * W3 - b[3] * W5;
    a4 = b[0] * W0 - b[4] * W0;
    a5 = b[3] * W3 + b[5] * W5;
    a6 = b[2] * W6 - b[6] * W2;
    a7 = b[1] * W7 - b[7] * W1;

    // Scale and round intermediate sums
    s1 = (181 * (a7 + a1 - a5 - a3) + 128) >> 8;
    s2 = (181 * (a3 + a1 - a5 - a7) + 128) >> 8;

    // Final butterfly operations and store back to the buffer
    b[0] = (a5 + a1 + a2 + a0 + 128) >> 8;
    b[1] = (s1 + a6 + a4 + 128) >> 8;
    b[2] = (s2 + a4 - a6 + 128) >> 8;
    b[3] = (a3 + a7 + a0 - a2 + 128) >> 8;
    b[4] = (a0 - a2 - a7 - a3 + 128) >> 8;
    b[5] = (a4 - a6 - s2 + 128) >> 8;
    b[6] = (a6 + a4 - s1 + 128) >> 8;
    b[7] = (a2 + a0 - a1 - a5 + 128) >> 8;
}