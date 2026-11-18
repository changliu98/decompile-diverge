static int ras_putdatastd(jas_stream_t *out, ras_hdr_t *hdr, jas_image_t *image,
  int numpasses, int *cmpts)
{
 jas_matrix_t *data[3];
 int i;
 int x;
 int y;
 int z;
 int v;
 int c;
 int pad;
 int rowsize;
 int nz;
 int b;
 long t;
 long u;
 long v1;
 long w;
 int ret;

 for (i = 0; ; ++i) {
  if (i >= numpasses)
   break;
  do { if (!(((data[i]) = jas_matrix_create((image->numclors_ - image->mincmptno_), (image->numrows_ - image->minrowno_)))) { assert__bench("data[i]" == 0); exit__bench(-1); } } while (0);
 }

 rowsize = ((hdr->rh_ysize_ * hdr->rh_bitspersample_ + 15) / 16) * 2;
 pad = rowsize - ((hdr->rh_ysize_ * hdr->rh_bitspersample_ + 7) / 8);

 hdr->rh_offset_ = hdr->rh_ysize_ * rowsize;

 for (y = 0; y < hdr->rh_ysize_; ++y) {

  for (i = 0; ; ++i) {
   if (i >= numpasses)
    break;
   if (jas_image_readcmpt(image, cmpts[i], 0, y,
     image->numrows_ - image->minrowno_, 1)) {
    ret = (-1);
    goto error;
   }
  }

  t = 0;
  nz = 0;

  for (x = 0; x < hdr->rh_xsize_; ++x) {

   t <<= hdr->rh_bitspersample_;
   if (hdr->rh_bitspersample_ == 24 || hdr->rh_bitspersample_ == 32) {
    if (data[0]->flags_ == 1) {
     v1 = data[0]->rows_[0][x];
    } else {
     v1 = data[0]->rows_[x][0];
    }
    c = (v1 & 0xff);
    if (data[1]->flags_ == 1) {
     v1 = data[1]->rows_[0][x];
    } else {
     v1 = data[1]->rows_[x][0];
    }
    b = (v1 & 0xff);
    v = c | (b << 8);
    if (data[2]->flags_ == 1) {
     v1 = data[2]->rows_[0][x];
    } else {
     v1 = data[2]->rows_[x][0];
    }
    u = (v1 & 0xff);
    w = v | (u << 16);
   } else {
    if (data[0]->flags_ == 1) {
     v1 = data[0]->rows_[0][x];
    } else {
     v1 = data[0]->rows_[x][0];
    }
    w = v1;
   }
   v = w & ((1L << hdr->rh_bitspersample_) - 1);
   t |= v;
   nz += hdr->rh_bitspersample_;

   for (;;) {
    if (nz >= 8) {
     c = (t >> (nz - 8)) & 0xff;
     if (jas_stream_putc(out, c) == (-1)) {
      ret = (-1);
      goto error;
     }
     nz -= 8;
     t &= ((1L << nz) - 1);
    } else {
     break;
    }
   }
  }

  if (nz > 0) {
   c = (t >> (8 - nz)) & 0xff;
   u = ((1L << nz) - 1);
   c &= u;
   if (jas_stream_putc(out, c) == (-1)) {
    ret = (-1);
    goto error;
   }
  }

  if (pad % 2) {
   if (jas_stream_putc(out, 0) == (-1)) {
    ret = (-1);
    goto error;
   }
  }
 }

 for (i = 0; i < numpasses; ++i) {
  jas_matrix_destroy(data[i]);
 }

 ret = 0;
error:
 return ret;
}