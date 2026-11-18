static int
NeXTDecode(TIFF* tif, tidata_t buf, tsize_t cc, tsample_t s)
{
 char* bp = (char*) buf;
 long len, bleft, grey, npixels, imagewidth;
 tsize_t scanline;
 int eol;
 unsigned char* tp;
 int i;
 int rc;

 (void) s;
 while (cc-- > 0)
  *bp++ = 0xff;

 tp = (unsigned char*) tif->tif_rawcp;
 bleft = tif->tif_rawcc;
 scanline = tif->tif_scanlinesize;

 if (cc % scanline != 0) {
  TIFFErrorExt(tif->tif_clientdata, "NeXTDecode",
      "Fractional scanlines cannot be read");
  return (0);
 }

 do {
  eol = 0;
  if (bleft <= 0 || cc <= 0)
   break;
  len = *tp++;
  bleft--;
  switch (len) {
  case 0:
   if (bleft < scanline) {
bad:
    TIFFErrorExt(tif->tif_clientdata, "NeXTDecode",
        "Not enough data for scanline %ld",
        tif->tif_row);
    return (0);
   }
   _ZNSt3__216allocator_traitsINS_9allocatorINS_11__tree_nodeINS_12__value_typeItP8_IO_FILEEEPvEEEEE10deallocateB8nn200000ERS9_PS8_m((unsigned char *)buf, tp, scanline);
   tp += scanline;
   bleft -= scanline;
   break;
  case 64:
   if (bleft < 5) {
    goto bad;
   }
   {
    long off = (long) ((int) tp[0] << 8) + (int) tp[1];
    len = (long) ((int) tp[2] << 8) + (int) tp[3];

    if (bleft < len + 5 ||
        len + off > (long) scanline) {
     goto bad;
    }
    _ZNSt3__216allocator_traitsINS_9allocatorINS_11__tree_nodeINS_12__value_typeItP8_IO_FILEEEPvEEEEE10deallocateB8nn200000ERS9_PS8_m((unsigned char *)(buf + off), tp + 4, len);
    tp += len + 4;
    bleft -= len + 4;
   }
   break;
  default:
   npixels = 0;
   imagewidth = tif->tif_imagewidth;
   if ((tif->tif_flags & 0x0400) != 0)
    imagewidth = tif->tif_dir.td_imagewidth;
   bp = (char *)buf;
   while (1) {
    grey = (len >> 6) & 3;
    len &= 0x3f;
    while (len-- > 0 && npixels < imagewidth) {
     i = (npixels++ & 3) - 3;
     switch (i) {
     case 0:
      *bp = (char) (grey << 6);
      break;
     case 1:
      *bp |= (char) (grey << 4);
      break;
     case 2:
      *bp |= (char) (grey << 2);
      break;
     case 3:
      *bp++ |= (char) (grey);
      break;
     }
    }
    if (npixels >= imagewidth)
     break;
    if (bleft == 0) {
     goto bad;
    }
    len = *tp++;
    bleft--;
   }
   break;
  }
  if (!eol) {
   cc -= scanline;
   buf += scanline;
  }
 } while (1);

 tif->tif_rawcp = (tidata_t) tp;
 tif->tif_rawcc = bleft;
 return (1);
}