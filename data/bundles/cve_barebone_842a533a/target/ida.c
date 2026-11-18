tmsize_t __cdecl TIFFReadEncodedStrip(TIFF *tif, uint32 strip, void *buf, tmsize_t size)
{
  tmsize_t stripsize; // [rsp+0h] [rbp-50h]
  uint32 rows; // [rsp+Ch] [rbp-44h]
  uint32 stripsperplane; // [rsp+18h] [rbp-38h]
  uint32 rowsperstrip; // [rsp+1Ch] [rbp-34h]

  if ( !TIFFCheckRead(tif, 0) )
    return -1LL;
  if ( strip < tif->tif_dir.td_nstrips )
  {
    rowsperstrip = tif->tif_dir.td_rowsperstrip;
    if ( rowsperstrip > tif->tif_dir.td_imagelength )
      rowsperstrip = tif->tif_dir.td_imagelength;
    stripsperplane = (rowsperstrip + tif->tif_dir.td_imagelength - 1) / rowsperstrip;
    rows = tif->tif_dir.td_imagelength - rowsperstrip * (strip % stripsperplane);
    if ( rows > rowsperstrip )
      rows = rowsperstrip;
    stripsize = TIFFVStripSize(tif, rows);
    if ( stripsize )
    {
      if ( tif->tif_dir.td_compression != 1
        || size == -1
        || size < stripsize
        || (tif->tif_flags & 0x800) != 0
        || (tif->tif_flags & 0x20000) != 0 )
      {
        if ( size != -1 && size < stripsize )
          stripsize = size;
        if ( !TIFFFillStrip(tif, strip) )
          return -1LL;
        if ( tif->tif_decodestrip(tif, (uint8 *)buf, stripsize, strip / stripsperplane) <= 0 )
          return -1LL;
      }
      else
      {
        if ( TIFFReadRawStrip1(tif, strip, buf, stripsize, "TIFFReadEncodedStrip") != stripsize )
          return -1LL;
        if ( (tif->tif_dir.td_fillorder & tif->tif_flags) == 0 && (tif->tif_flags & 0x100) == 0 )
          TIFFReverseBits((uint8 *)buf, stripsize);
      }
      tif->tif_postdecode(tif, (uint8 *)buf, stripsize);
      return stripsize;
    }
    return -1LL;
  }
  else
  {
    TIFFErrorExt(
      tif->tif_clientdata,
      "TIFFReadEncodedStrip",
      "%lu: Strip out of range, max %lu",
      strip,
      tif->tif_dir.td_nstrips);
    return -1LL;
  }
}