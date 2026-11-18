int mpeg3video_idctrow(short *blk)
{
    int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    int tmp10, tmp11, tmp12, tmp13;
    int z1, z2, z3, z4, z5, z6, z7, z8;
    int s0, s1, s2, s3, s4, s5, s6, s7;

    if (!blk[0] && !blk[1] && !blk[2] && !blk[3] && !blk[4] && !blk[5] && !blk[6] && !blk[7])
    {
        blk[0] = blk[1] = blk[2] = blk[3] = blk[4] = blk[5] = blk[6] = blk[7] = blk[0] * 8;
        return 0;
    }

    z1 = (blk[0] * 2048) + 128;
    z2 = (blk[2] * 2048);
    z3 = (blk[4] * 2048);
    z4 = (blk[6] * 2048);

    tmp0 = (blk[1] * 2048) + (blk[7] * 2048);
    tmp1 = (blk[1] * 2048) - (blk[7] * 2048);
    tmp2 = (blk[5] * 2048) + (blk[3] * 2048);
    tmp3 = (blk[5] * 2048) - (blk[3] * 2048);

    tmp10 = z1 + z3;
    tmp12 = z1 - z3;
    tmp11 = z2 + z4;
    tmp13 = z2 - z4;

    z1 = tmp10 + tmp11;
    z2 = tmp10 - tmp11;
    z3 = tmp12 + tmp13;
    z4 = tmp12 - tmp13;

    s0 = z1 + tmp2;
    s1 = z2 + tmp3;
    s2 = z3 + tmp1;
    s3 = z4 + tmp0;
    s4 = z4 - tmp0;
    s5 = z3 - tmp1;
    s6 = z2 - tmp3;
    s7 = z1 - tmp2;

    blk[0] = (s0 >> 8);
    blk[1] = (s1 >> 8);
    blk[2] = (s2 >> 8);
    blk[3] = (s3 >> 8);
    blk[4] = (s4 >> 8);
    blk[5] = (s5 >> 8);
    blk[6] = (s6 >> 8);
    blk[7] = (s7 >> 8);

    return 1;
}