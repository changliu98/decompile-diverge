tmsize_t
TIFFReadEncodedStrip(TIFF* tif, uint32 strip, tdata_t buf, tmsize_t size)
{
 static const char module[] = "TIFFReadEncodedStrip";
 TIFFDirectory *td = &tif->tif_dir;
 uint32 rowsperstrip;
 uint32 nstrips;
 uint32 row;
 uint16 plane;
 tmsize_t cc;

 if (!TIFFCheckRead(tif, 0))
  return ((tmsize_t) -1);

 if (strip >= td->td_nstrips) {
  TIFFErrorExt(tif->tif_clientdata, module, "%lu: Strip out of range, max %lu",
      (unsigned long) strip,
      (unsigned long) td->td_nstrips);
  return ((tmsize_t) -1);
 }

 rowsperstrip = td->td_rowsperstrip;
 if (rowsperstrip > td->td_imagelength)
  rowsperstrip = td->td_imagelength;
 nstrips = (td->td_imagelength + rowsperstrip - 1) / rowsperstrip;
 row = (strip % nstrips) * rowsperstrip;
 if (row > td->td_imagelength)
  row = td->td_imagelength;

 cc = TIFFVStripSize(tif, row);
 if (cc == 0)
  return ((tmsize_t) -1);

 if (td->td_compression == 1 &&
     size != (tmsize_t) -1 && cc <= size &&
     !(((tif)->tif_flags & 0x0000800) != 0) && !(((tif)->tif_flags & 0x00020000) != 0)) {
  if (TIFFReadRawStrip1(tif, strip, buf, cc, module) != cc)
   return ((tmsize_t) -1);

  if (!(((tif)->tif_flags & (td->td_fillorder)) != 0) && !(((tif)->tif_flags & 0x00000100) != 0))
   TIFFReverseBits(buf, cc);

  (*tif->tif_postdecode)(tif, buf, cc);
  return (cc);
 }

 if (size != (tmsize_t) -1 && cc > size)
  cc = size;

 if (!TIFFFillStrip(tif, strip))
  return ((tmsize_t) -1);

 plane = (uint16)(strip / nstrips);
 if ((*(tif)->tif_decodestrip)(tif, buf, cc, plane) < 1)
  return ((tmsize_t) -1);

 (*tif->tif_postdecode)(tif, buf, cc);
 return (cc);
}