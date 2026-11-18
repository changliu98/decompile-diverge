int ras_putdatastd(jas_stream_t *out, ras_hdr_t *hdr, jas_image_t *image,
  int numcmpts, int *cmpts)
{
 jas_matrix_t *data[3];
 int i;
 int c;
 int y;
 int x;
 int v;
 int nz;
 int z;
 int pad;
 int rowsize;
 int eof;

 for (i = 0; i < numcmpts; ++i) {
  data[i] = jas_matrix_create(image->bry_ - image->tly_,
   image->brx_ - image->tlx_);
  do { if (!(data[i])) __assert_fail("data[i]","/work/harness.c",246,"int ras_putdatastd(jas_stream_t *, ras_hdr_t *, jas_image_t *, int, int *)"); } while (0);
 }

 rowsize = (hdr->width * hdr->depth + 15) / 16 * 2;
 hdr->length = hdr->height * rowsize;

 for (y = 0; y < hdr->height; ++y) {
  for (i = 0; i < numcmpts; ++i) {
   if (jas_image_readcmpt(image, cmpts[i], 0, y,
    image->brx_ - image->tlx_, 1, data[i]))
    return -1;
  }
  z = 0;
  nz = 0;
  for (x = 0; x < hdr->width; ++x) {
   if (hdr->depth == 24 || hdr->depth == 32) {
    v = (data[0]->numrows_ == 1 ? (int)(data[0]->rows_[0][x]) : (int)(data[0]->rows_[x][0])) & 0xff;
    v |= ((data[1]->numrows_ == 1 ? (int)(data[1]->rows_[0][x]) : (int)(data[1]->rows_[x][0])) & 0xff) << 8;
    v |= ((data[2]->numrows_ == 1 ? (int)(data[2]->rows_[0][x]) : (int)(data[2]->rows_[x][0])) & 0xff) << 16;
   } else {
    v = (data[0]->numrows_ == 1 ? (int)(data[0]->rows_[0][x]) : (int)(data[0]->rows_[x][0]));
   }
   v &= (hdr->depth == 32) ? 0xffffffff : (1L << hdr->depth) - 1;
   z = (z << hdr->depth) | v;
   nz += hdr->depth;
   while (nz >= 8) {
    if (jas_stream_putc(out, (z >> (nz - 8)) & 0xff) == -1)
     return -1;
    nz -= 8;
    z &= (nz == 32) ? 0xffffffff : (1L << nz) - 1;
   }
  }
  if (nz > 0) {
   if (jas_stream_putc(out, (z >> (8 - nz)) & ((nz == 32) ? 0xffffffff : (1L << nz) - 1)) == -1)
    return -1;
  }
  pad = (rowsize - ((hdr->width * hdr->depth + 7) / 8)) % 2;
  if (pad) {
   if (jas_stream_putc(out, 0) == -1)
    return -1;
  }
 }

 for (i = 0; i < numcmpts; ++i)
  jas_matrix_destroy(data[i]);

 return 0;
}