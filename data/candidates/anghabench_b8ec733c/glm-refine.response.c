void __cdecl vc1_inv_trans_8x8_c(int16_t *block)
{
    int16_t temp[64];
    int16_t (*src)[8] = (int16_t (*)[8])block;
    int16_t (*dst)[8] = (int16_t (*)[8])temp;
    int t1, t2, t3, t4, t5, t6, t7, t8;

    // 1st Pass: Column processing (reads rows from 'block', writes columns to 'temp')
    // The original code increments src by 1 and dst by 8, meaning it transposes the matrix.
    for (int i = 0; i < 8; ++i)
    {
        // Even part (Butterfly)
        t1 = 12 * (src[i][4] + src[i][0]) + 4;
        t2 = 12 * (src[i][0] - src[i][4]) + 4;
        t3 = 6 * src[i][6] + 16 * src[i][2];
        t4 = 6 * src[i][2] - 16 * src[i][6];
        
        t5 = t3 + t1;
        t6 = t4 + t2;
        t7 = t2 - t4;
        t8 = t1 - t3;

        // Odd part (Matrix multiplication)
        t1 =  4 * src[i][7] +  9 * src[i][5] + 15 * src[i][3] + 16 * src[i][1];
        t2 = 15 * src[i][1] -  4 * src[i][3] - 16 * src[i][5] -  9 * src[i][7];
        t3 = 15 * src[i][7] +  4 * src[i][5] +  9 * src[i][1] - 16 * src[i][3];
        t4 = 15 * src[i][5] +  4 * src[i][1] -  9 * src[i][3] - 16 * src[i][7];

        // Combine and scale
        dst[0][i] = (t1 + t5) >> 3;
        dst[1][i] = (t2 + t6) >> 3;
        dst[2][i] = (t3 + t7) >> 3;
        dst[3][i] = (t4 + t8) >> 3;
        dst[4][i] = (t8 - t4) >> 3;
        dst[5][i] = (t7 - t3) >> 3;
        dst[6][i] = (t6 - t2) >> 3;
        dst[7][i] = (t5 - t1) >> 3;
    }

    // 2nd Pass: Row processing (reads columns from 'temp', writes rows to 'block')
    // The original code increments src by 1 and dst by 1, processing rows.
    src = (int16_t (*)[8])temp;
    dst = (int16_t (*)[8])block;
    
    for (int i = 0; i < 8; ++i)
    {
        // Even part (Butterfly)
        t1 = 12 * (src[i][4] + src[i][0]) + 64;
        t2 = 12 * (src[i][0] - src[i][4]) + 64;
        t3 = 6 * src[i][6] + 16 * src[i][2];
        t4 = 6 * src[i][2] - 16 * src[i][6];
        
        t5 = t3 + t1;
        t6 = t4 + t2;
        t7 = t2 - t4;
        t8 = t1 - t3;

        // Odd part (Matrix multiplication)
        t1 =  4 * src[i][7] +  9 * src[i][5] + 15 * src[i][3] + 16 * src[i][1];
        t2 = 15 * src[i][1] -  4 * src[i][3] - 16 * src[i][5] -  9 * src[i][7];
        t3 = 15 * src[i][7] +  4 * src[i][5] +  9 * src[i][1] - 16 * src[i][3];
        t4 = 15 * src[i][5] +  4 * src[i][1] -  9 * src[i][3] - 16 * src[i][7];

        // Combine and scale (with rounding adjustment +1 for negative results)
        dst[i][0] = (t1 + t5) >> 7;
        dst[i][1] = (t2 + t6) >> 7;
        dst[i][2] = (t3 + t7) >> 7;
        dst[i][3] = (t4 + t8) >> 7;
        dst[i][4] = (t8 - t4 + 1) >> 7;
        dst[i][5] = (t7 - t3 + 1) >> 7;
        dst[i][6] = (t6 - t2 + 1) >> 7;
        dst[i][7] = (t5 - t1 + 1) >> 7;
    }
}