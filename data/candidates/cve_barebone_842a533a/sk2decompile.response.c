tsize_t TIFFReadEncodedStrip(TIFF* tif, tstrip_t strip, void* buf,
                             tsize_t size) {
  tsize_t cc;
  tstrip_t stripsperimage;
  tstrip_t stripsperrow;
  tstrip_t rowsperstrip;
  if (!TIFFCheckRead(tif, 0)) return ((tsize_t)-1);
  if (strip >= tif->tif_dir.tif_nstrips) {
    TIFFErrorExt(tif->tif_clientdata, "TIFFReadEncodedStrip",
                 "%lu: Strip out of range, max %lu", (unsigned long)strip,
                 (unsigned long)tif->tif_dir.tif_nstrips);
    return ((tsize_t)-1);
  }
  rowsperstrip = tif->tif_dir.tif_rowsperstrip;
  if (rowsperstrip > tif->tif_dir.tif_imagelength)
    rowsperstrip = tif->tif_dir.tif_imagelength;
  stripsperimage = (rowsperstrip + tif->tif_dir.tif_imagelength - 1) /
                   rowsperstrip;
  stripsperrow = strip % stripsperimage;
  stripsperrow = tif->tif_dir.tif_imagelength - stripsperrow * rowsperstrip;
  if (stripsperrow > rowsperstrip) stripsperrow = rowsperstrip;
  cc = TIFFVStripSize(tif, stripsperrow);
  if (cc == 0) return ((tsize_t)-1);
  if (tif->tif_dir.tif_fillorder == 1 && size != (tsize_t)(-1) && size >= cc &&
      !(tif->tif_flags & 0x00000800) && !(tif->tif_flags & 0x00020000)) {
    if (TIFFReadRawStrip1(tif, strip, buf, cc, "TIFFReadEncodedStrip") != cc)
      return ((tsize_t)-1);
    if (!(tif->tif_flags & tif->tif_dir.tif_bitspersample) &&
        !(tif->tif_flags & 0x0100))
      TIFFReverseBits(buf, cc);
  } else {
    if (size != (tsize_t)(-1) && size < cc) cc = size;
    if (TIFFFillStrip(tif, strip) == 0) return ((tsize_t)-1);
    if (tif->tif_decoderow(tif, buf, cc, strip / stripsperimage) <= 0)
      return ((tsize_t)-1);
  }
  (*tif->tif_postdecode)(tif, buf, cc);
  return (cc);
}