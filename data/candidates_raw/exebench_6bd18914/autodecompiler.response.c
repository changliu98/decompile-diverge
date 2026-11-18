void idct_row(signed short *blk, signed short *out)
{
 signed int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
 signed int tmp10, tmp11, tmp12, tmp13;
 signed int z5, z10, z11, z12, z13;
 signed short *blkptr;
 signed short *dataptr;
 signed int d0, d1, d2, d3, d4, d5, d6, d7;
 signed int i;
 signed int j;




 blkptr = blk;
 dataptr = out;
 for (i = 0; i < 5; i++) {
  tmp0 = blkptr[0] + blkptr[12];
  tmp1 = blkptr[4] + blkptr[8];
  tmp2 = blkptr[4] - blkptr[8];
  tmp3 = blkptr[0] - blkptr[12];

  tmp10 = tmp0 + tmp1;
  tmp11 = tmp2 + tmp3;
  tmp12 = tmp0 - tmp1;
  tmp13 = tmp3 - tmp2;

  dataptr[0] = tmp10 + tmp11;
  dataptr[4] = tmp12 + tmp13;
  dataptr[8] = tmp10 - tmp11;
  dataptr[12] = tmp13 - tmp12;

  blkptr++;
  dataptr++;
 }




 blkptr = out;
 dataptr = out;
 for (i = 0; i < 5; i++) {
  tmp0 = blkptr[0] + blkptr[3];
  tmp1 = blkptr[1] + blkptr[2];
  tmp2 = blkptr[1] - blkptr[2];
  tmp3 = blkptr[0] - blkptr[3];

  tmp10 = tmp0 + tmp1;
  tmp11 = tmp2 + tmp3;
  tmp12 = tmp0 - tmp1;
  tmp13 = tmp3 - tmp2;

  d0 = (tmp10 + 3) >> 3;
  d1 = (tmp11 + 3) >> 3;
  d2 = (tmp12 + 3) >> 3;
  d3 = (tmp13 + 3) >> 3;

  dataptr[0] = d0;
  dataptr[1] = d1;
  dataptr[2] = d2;
  dataptr[3] = d3;

  blkptr += 4;
  dataptr += 4;
 }






 for (i = 0; i < 17; i++)
  out[i << 4] = out[i];
}