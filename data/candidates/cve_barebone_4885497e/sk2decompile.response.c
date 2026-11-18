static int ras_putdatastd(jas_stream_t *out, jas_stream_rasheader_t *hdr,
                          jas_image_t *image, int numcmpts, int *cmptindices) {
  jas_matrix_t *cmptdata[3];
  int i;
  int y;
  int row;
  int bytesperline;
  int padbytes;
  int bitbuf;
  int bitcnt;
  int pixel;
  int byte;
  for (i = 0; i < numcmpts; ++i) {
    if (!(cmptdata[i] = jas_matrix_create(
              image->width - image->clx, image->height - image->cly))) {
      assert(cmptdata[i]);
      return -1;
    }
  }
  bytesperline = (hdr->bpp * hdr->width + 15) / 16 * 2;
  padbytes = bytesperline - (hdr->bpp * hdr->width + 7) / 8;
  hdr->length = hdr->height * bytesperline;
  for (y = 0; y < hdr->height; ++y) {
    for (i = 0; i < numcmpts; ++i) {
      if (jas_image_readcmpt(image, cmptindices[i], 0, y,
                             image->height - image->cly, 1, cmptdata[i])) {
        return -1;
      }
    }
    bitbuf = 0;
    bitcnt = 0;
    for (row = 0; row < hdr->width; ++row) {
      bitbuf <<= hdr->bpp;
      if (hdr->bpp == 24 || hdr->bpp == 32) {
        pixel = (((cmptdata[0]->numrows_ == 1 ? cmptdata[0]->rows_[0]
                                              : cmptdata[0]->rows_[row]) &
                  0xff)
                 << 16) |
                (((cmptdata[1]->numrows_ == 1 ? cmptdata[1]->rows_[0]
                                              : cmptdata[1]->rows_[row]) &
                  0xff)
                 << 8) |
                ((cmptdata[2]->numrows_ == 1 ? cmptdata[2]->rows_[0]
                                             : cmptdata[2]->rows_[row]) &
                 0xff);
      } else {
        pixel = (cmptdata[0]->numrows_ == 1 ? cmptdata[0]->rows_[0]
                                            : cmptdata[0]->rows_[row]);
      }
      bitbuf |= pixel & (hdr->bpp == 32 ? 0xffffffff : (1L << hdr->bpp) - 1);
      bitcnt += hdr->bpp;
      while (bitcnt >= 8) {
        byte = (bitbuf >> (bitcnt - 8)) & 0xff;
        if (jas_stream_putc(out, byte) == -1) return -1;
        bitcnt -= 8;
        bitbuf &= bitcnt == 32 ? 0xffffffff : (1L << bitcnt) - 1;
      }
    }
    if (bitcnt > 0) {
      byte = (bitbuf >> (8 - bitcnt)) & ((1 << bitcnt) - 1);
      if (jas_stream_putc(out, byte) == -1) return -1;
    }
    if (padbytes % 2) {
      if (jas_stream_putc(out, 0) == -1) return -1;
    }
  }
  for (i = 0; i < numcmpts; ++i) {
    jas_matrix_destroy(cmptdata[i]);
  }
  return 0;
}