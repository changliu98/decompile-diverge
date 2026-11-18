int NeXTDecode(TIFF *tif,uint8 *buf,tmsize_t occ,uint16 s)

{
  long c;
  int iVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  uint32 uVar5;
  byte *s_00;
  uint32 imagewidth;
  uint32 grey;
  uint32 npixels;
  tmsize_t off;
  tmsize_t n;
  tmsize_t scanline;
  uint8 *row;
  tmsize_t cc;
  uchar *op;
  uchar *bp;
  uint16 s_local;
  tmsize_t occ_local;
  uint8 *buf_local;
  TIFF *tif_local;
  int local_c;
  
  cc = occ;
  op = buf;
  while (0 < cc) {
    *op = 0xff;
    cc = cc + -1;
    op = op + 1;
  }
  bp = tif->tif_rawcp;
  cc = tif->tif_rawcc;
  c = tif->tif_scanlinesize;
  row = buf;
  occ_local = occ;
  if (occ % c == 0) {
    for (; 0 < cc && 0 < occ_local; occ_local = occ_local - c) {
      s_00 = bp + 1;
      n = (tmsize_t)*bp;
      cc = cc + -1;
      if (n == 0) {
        if (cc < c) goto LAB_00101957;
        _TIFFmemcpy(row,s_00,c);
        bp = s_00 + c;
        cc = cc - c;
      }
      else if (n == 0x40) {
        if (cc < 4) {
LAB_00101957:
          TIFFErrorExt(tif->tif_clientdata,"NeXTDecode","Not enough data for scanline %ld",
                       (ulong)tif->tif_row);
          return 0;
        }
        lVar3 = (long)(int)((uint)*s_00 * 0x100 + (uint)bp[2]);
        lVar4 = (long)(int)((uint)bp[3] * 0x100 + (uint)bp[4]);
        if ((cc < lVar4 + 4) || (c < lVar3 + lVar4)) goto LAB_00101957;
        _TIFFmemcpy(row + lVar3,bp + 5,lVar4);
        bp = s_00 + lVar4 + 4;
        cc = cc - (lVar4 + 4);
      }
      else {
        npixels = 0;
        imagewidth = (tif->tif_dir).td_imagewidth;
        if ((tif->tif_flags & 0x400) != 0) {
          imagewidth = (tif->tif_dir).td_tilewidth;
        }
        op = row;
        bp = s_00;
        while( true ) {
          lVar3 = n >> 6;
          iVar1 = (int)lVar3;
          n = n & 0x3f;
          while (lVar4 = n + -1, 0 < n && npixels < imagewidth) {
            uVar5 = npixels + 1;
            uVar2 = npixels & 3;
            npixels = uVar5;
            n = lVar4;
            switch(uVar2) {
            case 0:
              *op = (uchar)(iVar1 << 6);
              break;
            case 1:
              *op = *op | (byte)(iVar1 << 4);
              break;
            case 2:
              *op = *op | (byte)(iVar1 << 2);
              break;
            case 3:
              *op = *op | (byte)lVar3;
              op = op + 1;
            }
          }
          if (imagewidth <= npixels) break;
          if (cc == 0) goto LAB_00101957;
          n = (tmsize_t)*bp;
          cc = cc + -1;
          bp = bp + 1;
        }
      }
      row = row + c;
    }
    tif->tif_rawcp = bp;
    tif->tif_rawcc = cc;
    local_c = 1;
  }
  else {
    TIFFErrorExt(tif->tif_clientdata,"NeXTDecode","Fractional scanlines cannot be read");
    local_c = 0;
  }
  return local_c;
}