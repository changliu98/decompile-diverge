long TIFFReadEncodedStrip(struct tiff *tif, unsigned int strip, void *buf, unsigned long size)
{
  unsigned int rowsperstrip; unsigned int rows; unsigned int stripsperplane;
  unsigned long stripsize;
  if (!TIFFCheckStrip(tif, 0))
    return (0 - 1);
  if (strip >= tif->tif_dir.td_nstrips) {
    TIFFWarning(tif->tif_clientdata, "TIFFReadEncodedStrip",
        "%lu: Strip out of range, max %lu",
        (unsigned long)strip, (unsigned long)tif->tif_dir.td_nstrips);
    return (0 - 1);
  }
  rowsperstrip = tif->tif_dir.td_rowsperstrip;
  if (rowsperstrip > tif->tif_dir.td_imagelength)
    rowsperstrip = tif->tif_dir.td_imagelength;
  stripsperplane = (tif->tif_dir.td_imagelength + rowsperstrip - 1)
    / rowsperstrip;
  rows = tif->tif_dir.td_imagelength -
    (strip % stripsperplane) * rowsperstrip;
  if (rows > rowsperstrip)
    rows = rowsperstrip;
  if ((stripsize = TIFFStripSize(tif, rows)) == 0)
    return (0 - 1);
  if (tif->tif_dir.td_compression == 1
      && (size != (0 - 1))
      && (size >= stripsize)
      && !(tif->tif_flags & (1 << (sizeof(tif->tif_flags) * 8 - 1)))
      && !(tif->tif_flags & (1 << (17)))) {
    if (TIFFReadEncodedData(tif, strip, buf, stripsize) != (long)stripsize)
      return (0 - 1);
    if (tif->tif_dir.td_fillorder & tif->tif_flags
        && !(tif->tif_flags & (1 << (8))))
      TIFFSwapData(buf, stripsize);
  } else if (size != (0 - 1) && (size < stripsize))
    stripsize = size;
  else {
    if (!TIFFReadRawStrip(tif, strip))
      return (0 - 1);
    if (tif->tif_decodestrip(tif, (unsigned char *)buf,
        stripsize, strip / stripsperplane) <= 0)
      return (0 - 1);
  }
  tif->tif_postdecode(tif, (unsigned char *)buf, stripsize);
  return (long)stripsize;
}