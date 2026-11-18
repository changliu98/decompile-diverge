int __cdecl ras_putdatastd(jas_stream_t *out, ras_hdr_t *hdr, jas_image_t *image, int numcmpts, int *cmpts)
{
  __int64 v6; // [rsp+18h] [rbp-C8h]
  __int64 v7; // [rsp+20h] [rbp-C0h]
  jas_seqent_t v8; // [rsp+30h] [rbp-B0h]
  jas_seqent_t v9; // [rsp+38h] [rbp-A8h]
  jas_seqent_t v10; // [rsp+48h] [rbp-98h]
  jas_seqent_t v11; // [rsp+58h] [rbp-88h]
  int i; // [rsp+6Ch] [rbp-74h]
  int ia; // [rsp+6Ch] [rbp-74h]
  int ib; // [rsp+6Ch] [rbp-74h]
  jas_matrix_t *data[3]; // [rsp+70h] [rbp-70h]
  int v; // [rsp+90h] [rbp-50h]
  int y; // [rsp+94h] [rbp-4Ch]
  int x; // [rsp+98h] [rbp-48h]
  int c; // [rsp+9Ch] [rbp-44h]
  int nz; // [rsp+A0h] [rbp-40h]
  unsigned int z; // [rsp+A4h] [rbp-3Ch]
  int pad; // [rsp+A8h] [rbp-38h]
  int rowsize; // [rsp+ACh] [rbp-34h]
  int *cmptsa; // [rsp+B0h] [rbp-30h]
  int numcmptsa; // [rsp+BCh] [rbp-24h]
  jas_image_t *imagea; // [rsp+C0h] [rbp-20h]
  ras_hdr_t *hdra; // [rsp+C8h] [rbp-18h]
  jas_stream_t *outa; // [rsp+D0h] [rbp-10h]

  outa = out;
  hdra = hdr;
  imagea = image;
  numcmptsa = numcmpts;
  cmptsa = cmpts;
  for ( i = 0; i < numcmptsa; ++i )
  {
    data[i] = jas_matrix_create(
                LODWORD(imagea->bry_) - LODWORD(imagea->tly_),
                LODWORD(imagea->brx_) - LODWORD(imagea->tlx_));
    if ( !data[i] )
      __assert_fail(
        "data[i]",
        "/work/harness.c",
        0xF6u,
        "int ras_putdatastd(jas_stream_t *, ras_hdr_t *, jas_image_t *, int, int *)");
  }
  rowsize = 2 * ((hdra->depth * hdra->width + 15) / 16);
  pad = rowsize - (hdra->depth * hdra->width + 7) / 8;
  hdra->length = rowsize * hdra->height;
  for ( y = 0; y < hdra->height; ++y )
  {
    for ( ia = 0; ia < numcmptsa; ++ia )
    {
      if ( jas_image_readcmpt(imagea, cmptsa[ia], 0LL, y, imagea->brx_ - imagea->tlx_, 1LL, data[ia]) )
        return -1;
    }
    z = 0;
    nz = 0;
    for ( x = 0; x < hdra->width; ++x )
    {
      z <<= hdra->depth;
      if ( hdra->depth == 24 || hdra->depth == 32 )
      {
        if ( data[0]->numrows_ == 1 )
          v11 = (*data[0]->rows_)[x];
        else
          v11 = *data[0]->rows_[x];
        if ( data[1]->numrows_ == 1 )
          v10 = (*data[1]->rows_)[x];
        else
          v10 = *data[1]->rows_[x];
        if ( data[2]->numrows_ == 1 )
          v9 = (*data[2]->rows_)[x];
        else
          v9 = *data[2]->rows_[x];
        v = ((unsigned __int8)v9 << 16) | ((unsigned __int8)v10 << 8) | (unsigned __int8)v11;
      }
      else
      {
        if ( data[0]->numrows_ == 1 )
          v8 = (*data[0]->rows_)[x];
        else
          v8 = *data[0]->rows_[x];
        v = v8;
      }
      if ( hdra->depth == 32 )
        LODWORD(v7) = -1;
      else
        v7 = (1LL << hdra->depth) - 1;
      z |= v7 & v;
      nz += hdra->depth;
      while ( nz >= 8 )
      {
        c = (unsigned __int8)(z >> (nz - 8));
        if ( jas_stream_putc(outa, c) == -1 )
          return -1;
        nz -= 8;
        if ( nz == 32 )
          LODWORD(v6) = -1;
        else
          v6 = (1LL << nz) - 1;
        z &= v6;
      }
    }
    if ( nz > 0 )
    {
      c = ((1 << nz) - 1) & (z >> (8 - nz));
      if ( jas_stream_putc(outa, c) == -1 )
        return -1;
    }
    if ( pad % 2 && jas_stream_putc(outa, 0) == -1 )
      return -1;
  }
  for ( ib = 0; ib < numcmptsa; ++ib )
    jas_matrix_destroy(data[ib]);
  return 0;
}