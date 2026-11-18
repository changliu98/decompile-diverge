static int NeXTDecode(TIFFRGBAImage *img, unsigned char *cp, uint32 scanline,
                      unsigned short mode) {
  unsigned char *p;
  unsigned char *sp;
  unsigned char *lp;
  unsigned char *q;
  unsigned char code;
  unsigned char value;
  unsigned int offset;
  unsigned int length;
  unsigned int pos;
  unsigned int size;
  uint32 count;
  uint32 slen;
  unsigned char *sp1;
  p = cp;
  count = scanline;
  while (count-- > 0) *p++ = 0xff;
  sp = img->sp;
  slen = img->slen;
  count = img->width;
  if (scanline % count) {
    TIFFErrorExt(img->tif, "NeXTDecode",
                 "Fractional scanlines cannot be read");
    return (0);
  }
  lp = cp;
  while (slen > 0 && count > 0) {
    code = *sp++;
    slen--;
    if (code == 0) {
      if (slen < count) {
        TIFFErrorExt(img->tif, "NeXTDecode",
                     "Not enough data for scanline %ld", (long)img->row);
        return (0);
      }
      _TIFFmemcpy(lp, sp, count);
      sp += count;
      slen -= count;
    } else if (code == 0x40) {
      if (slen < 4) {
        TIFFErrorExt(img->tif, "NeXTDecode",
                     "Not enough data for scanline %ld", (long)img->row);
        return (0);
      }
      offset = sp[0] * 256 + sp[1];
      length = sp[2] * 256 + sp[3];
      sp += 4;
      slen -= 4;
      if (slen < length + 4 || offset + length > count) {
        TIFFErrorExt(img->tif, "NeXTDecode",
                     "Not enough data for scanline %ld", (long)img->row);
        return (0);
      }
      _TIFFmemcpy(lp + offset, sp, length);
      sp += length;
      slen -= length;
    } else {
      pos = 0;
      size = img->pixelaspect.x;
      if (img->flags & 0x0400) size = img->pixelaspect.y;
      q = lp;
      while (1) {
        value = (code >> 6) & 3;
        length = code & 0x3f;
        while (length-- > 0 && pos < size) {
          switch (pos++ & 3) {
            case 0:
              *q = value << 6;
              break;
            case 1:
              *q |= value << 4;
              break;
            case 2:
              *q |= value << 2;
              break;
            case 3:
              *q++ |= value;
              break;
          }
        }
        if (pos >= size) break;
        if (slen == 0) {
          TIFFErrorExt(img->tif, "NeXTDecode",
                       "Not enough data for scanline %ld", (long)img->row);
          return (0);
        }
        code = *sp++;
        slen--;
      }
    }
    count -= img->width;
    lp += img->width;
  }
  img->sp = sp;
  img->slen = slen;
  return (1);
}