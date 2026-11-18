void
njRowIDCT(int *blk)
{
   int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
   int tmp10, tmp11, tmp12, tmp13;
   int z1, z2, z3, z4, z5, z6, z7, z8;


   if (blk[0] == 0 && blk[1] == 0 && blk[2] == 0 && blk[3] == 0 &&
       blk[4] == 0 && blk[5] == 0 && blk[6] == 0 && blk[7] == 0) {
      blk[0] = blk[1] = blk[2] = blk[3] = blk[4] = blk[5] = blk[6] = blk[7] = blk[0] << 3;
      return;
   }

   z1 = (blk[0] << 11) + 128;
   tmp0 = blk[0] + blk[4];
   tmp1 = blk[0] - blk[4];


   z2 = ((blk[1] + blk[7]) * 373) + ((blk[1] * 2216) + (blk[7] * -3490));
   z3 = ((blk[1] * 2216) - (blk[7] * 3490)) + ((blk[1] + blk[7]) * 373);


   z4 = ((blk[2] + blk[6]) * 1108) + ((blk[2] * -2613) + (blk[6] * -4241));
   z5 = ((blk[2] * -2613) - (blk[6] * 4241)) + ((blk[2] + blk[6]) * 1108);


   z6 = ((blk[3] + blk[5]) * 2272) + ((blk[3] * -4241) + (blk[5] * -2613));
   z7 = ((blk[3] * -4241) - (blk[5] * 2613)) + ((blk[3] + blk[5]) * 2272);


   z8 = (blk[1] + blk[7]) * 1108;


   tmp10 = z1 + z2;
   tmp12 = z1 - z2;
   tmp11 = z3 + z4;
   tmp13 = z5 + z6;

   blk[0] = (tmp10 + tmp11) >> 8;
   blk[1] = (tmp12 + tmp13) >> 8;
   blk[2] = (tmp12 - tmp13) >> 8;
   blk[3] = (tmp10 - tmp11) >> 8;
   blk[4] = (tmp10 - tmp11) >> 8;
   blk[5] = (tmp12 - tmp13) >> 8;
   blk[6] = (tmp12 + tmp13) >> 8;
   blk[7] = (tmp10 + tmp11) >> 8;
}