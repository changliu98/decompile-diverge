void idctRows(void)
{
    short i, j;
    short *pSrc = gCoeffBuf;
    short a0, a1, a2, a3, a4, a5, a6, a7;
    short b0, b1, b2, b3, b4, b5, b6, b7;
    short t0, t1, t2, t3, t4, t5, t6, t7;

    for (i = 0; i < 8; i++)
    {
        if ((pSrc[1] == 0) && (pSrc[2] == 0) && (pSrc[3] == 0) &&
            (pSrc[4] == 0) && (pSrc[5] == 0) && (pSrc[6] == 0) &&
            (pSrc[7] == 0))
        {
            a0 = pSrc[0];
            pSrc[0] = a0;
            pSrc[1] = a0;
            pSrc[2] = a0;
            pSrc[3] = a0;
            pSrc[4] = a0;
            pSrc[5] = a0;
            pSrc[6] = a0;
            pSrc[7] = a0;
        }
        else
        {
            a0 = pSrc[0];
            a1 = pSrc[1];
            a2 = pSrc[2];
            a3 = pSrc[3];
            a4 = pSrc[4];
            a5 = pSrc[5];
            a6 = pSrc[6];
            a7 = pSrc[7];

            b0 = a0 + a4;
            b1 = a0 - a4;
            b2 = a2 + a6;
            t0 = a2 - a6;
            t0 = imul_b1_b3(t0);
            b3 = a1 - a7;
            t1 = a1 + a7;
            b4 = a5 - a3;
            t2 = a5 + a3;
            b5 = t1 - t2;
            t3 = t1 + t2;
            b6 = t0 - b2;
            t4 = t0 - b5;
            b7 = b6 + b1;
            t5 = b6 - b1;
            t6 = b4 - b7;
            t7 = b5 + b4;

            pSrc[0] = b0 + t3;
            pSrc[1] = b1 + t6;
            pSrc[2] = b2 + t5;
            pSrc[3] = b3 - t7;
            pSrc[4] = b3 + t7;
            pSrc[5] = b2 - t5;
            pSrc[6] = b1 - t6;
            pSrc[7] = b0 - t3;
        }

        pSrc += 8;
    }
}