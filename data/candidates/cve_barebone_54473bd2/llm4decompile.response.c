int
NeXTDecode(TIFF* tif, tidata_t buf, tmsize_t occ, uint16 s)
{
 static const char module[] = "NeXTDecode";
 uint8* cp = (uint8*) buf;
 tmsize_t rowsize = tif->tif_scanlinesize;
 uint32 imagewidth;

 (void) s;
 while (occ-- > 0)
  *cp++ = 0xff;

 cp = (uint8*) tif->tif_rawcp;
 occ = tif->tif_rawcc;
 if (occ % rowsize) {
  TIFFErrorExt(tif->tif_clientdata, module, "Fractional scanlines cannot be read");
  return (0);
 }

 while (occ > 0 && rowsize > 0) {
  uint8* row = cp;
  uint32 n = *cp++;
  occ--;
  if (n == 0) {
   if (occ < rowsize)
    goto bad;
   _TIFFmemcpy(buf, cp, rowsize);
   cp += rowsize;
   occ -= rowsize;
  } else if (n == 64) {
   uint32 off, size;

   if (occ < 4)
    goto bad;
   off = (cp[0]<<8) + cp[1];
   size = (cp[2]<<8) + cp[3];
   if (occ < size+4 || off+size > rowsize)
    goto bad;
   _TIFFmemcpy((char*) buf+off, cp+4, size);
   cp += size+4;
   occ -= size+4;
  } else {
   uint32 npixels = 0;
   uint8* op = (uint8*) buf;

   imagewidth = (tif->tif_flags & 0x0400) ?
       (tif->tif_dir).td_tilewidth : (tif->tif_dir).td_imagewidth;
   for (;;) {
    uint32 run = n>>6;

    n &= 0x3f;
    while (n-- > 0 && npixels < imagewidth) {
     switch (npixels++ & 0x03) {
     case 0:
      *op = run<<6;
      break;
     case 1:
      *op |= run<<4;
      break;
     case 2:
      *op |= run<<2;
      break;
     case 3:
      *op++ |= run;
      break;
     }
    }
    if (npixels >= imagewidth)
     break;
    if (occ == 0)
     goto bad;
    n = *cp++;
    occ--;
   }
  }
  buf = (tidata_t)((char*) buf + rowsize);
 }
 tif->tif_rawcp = (tidata_t) cp;
 tif->tif_rawcc = occ;
 return (1);
bad:
 TIFFErrorExt(tif->tif_clientdata, module, "Not enough data for scanline %ld",
     (long) tif->tif_row);
 return (0);
}