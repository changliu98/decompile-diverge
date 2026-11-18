tsize_t
TIFFReadEncodedStrip(TIFF* tif, tstrip_t strip, tdata_t buf, tsize_t size)
{
 TIFFDirectory *td = &tif->tif_dir;
 tsize_t bytecount;

 if (!TIFFCheckRead(tif, 0))
  return ((tsize_t) -1);
 if (strip >= td->td_nstrips) {
  TIFFErrorExt(tif->tif_clientdata, "TIFFReadEncodedStrip",
      "%lu: Strip out of range, max %lu", (unsigned long) strip,
      (unsigned long) td->td_nstrips);
  return ((tsize_t) -1);
 }
 if (td->td_planarconfig == 1) {
  uint32 rowsperstrip = td->td_rowsperstrip;
  if (rowsperstrip > td->td_imagelength)
   rowsperstrip = td->td_imagelength;
  {
   tsize_t stripsperrow = (td->td_imagewidth +
       td->td_tilewidth - 1) / td->td_tilewidth;
   uint32 stripinplane = strip % stripsperrow;
   unsigned short plane = (unsigned short)(strip / stripsperrow);
   uint32 row = stripinplane * rowsperstrip;
   if (row > td->td_imagelength)
    row = td->td_imagelength;
   if (size != (tsize_t)-1 && size < rowsperstrip)
    rowsperstrip = size;
   bytecount = TIFFVStripSize(tif, rowsperstrip);
   if (bytecount == 0)
    return ((tsize_t) -1);

   if ((((td)->td_fillorder == 1) && (size == (tsize_t)-1 || ((tsize_t)bytecount <= size) && !(((tif)->tif_flags & 0x00800) || ((tif)->tif_flags & 0x20000)))) {
    if (TIFFReadRawStrip1(tif, strip, buf, bytecount,
        "TIFFReadEncodedStrip") != bytecount)
     return ((tsize_t) -1);

    if (!((td)->td_fillorder == 1 && (((tif)->tif_flags & 0x00100) || ((td)->td_bitspersample * (td)->td_samplesperpixel < 8))))
     TIFFReverseBits((unsigned char *) buf, bytecount);
    (*tif->tif_postdecode)(tif, (unsigned char *) buf, bytecount);
    return (bytecount);
   } else {
    if (size != (tsize_t)-1 && size < bytecount)
     bytecount = size;
    if (!TIFFFillStrip(tif, strip))
     return ((tsize_t) -1);
    if (tif->tif_decoderow(tif, (unsigned char *) buf, bytecount,
        plane) <= 0)
     return ((tsize_t) -1);
    (*tif->tif_postdecode)(tif, (unsigned char *) buf, bytecount);
    return (bytecount);
   }
  }
 } else {
  if (size != (tsize_t)-1 && size < td->td_stripbytecount)
   bytecount = size;
  else
   bytecount = td->td_stripbytecount;
  if (!TIFFFillStrip(tif, strip))
   return ((tsize_t) -1);
  if (tif->tif_decodestrip(tif, (unsigned char *) buf, bytecount) <= 0)
   return ((tsize_t) -1);
  (*tif->tif_postdecode)(tif, (unsigned char *) buf, bytecount);
  return (bytecount);
 }
}