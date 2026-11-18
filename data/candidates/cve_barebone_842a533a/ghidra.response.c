tmsize_t TIFFReadEncodedStrip(TIFF *tif,uint32 strip,void *buf,tmsize_t size)

{
  int iVar1;
  uint uVar2;
  tmsize_t stripsize;
  uint32 rows;
  uint16 plane;
  uint32 stripinplane;
  uint32 stripsperplane;
  uint32 rowsperstrip;
  TIFFDirectory *td;
  tmsize_t size_local;
  void *buf_local;
  uint32 strip_local;
  TIFF *tif_local;
  tmsize_t local_10;
  
  iVar1 = TIFFCheckRead(tif,0);
  if (iVar1 == 0) {
    local_10 = -1;
  }
  else if (strip < (tif->tif_dir).td_nstrips) {
    rowsperstrip = (tif->tif_dir).td_rowsperstrip;
    if ((tif->tif_dir).td_imagelength < rowsperstrip) {
      rowsperstrip = (tif->tif_dir).td_imagelength;
    }
    uVar2 = (((tif->tif_dir).td_imagelength + rowsperstrip) - 1) / rowsperstrip;
    rows = (tif->tif_dir).td_imagelength - (strip % uVar2) * rowsperstrip;
    if (rowsperstrip < rows) {
      rows = rowsperstrip;
    }
    stripsize = TIFFVStripSize(tif,rows);
    if (stripsize == 0) {
      local_10 = -1;
    }
    else if (((((tif->tif_dir).td_compression == 1) && (size != -1)) && (stripsize <= size)) &&
            (((tif->tif_flags & 0x800) == 0 && ((tif->tif_flags & 0x20000) == 0)))) {
      iVar1 = TIFFReadRawStrip1(tif,strip,buf,stripsize,"TIFFReadEncodedStrip");
      if (iVar1 == stripsize) {
        if (((tif->tif_flags & (uint)(tif->tif_dir).td_fillorder) == 0) &&
           ((tif->tif_flags & 0x100) == 0)) {
          TIFFReverseBits(buf,stripsize);
        }
        (*tif->tif_postdecode)(tif,buf,stripsize);
        local_10 = stripsize;
      }
      else {
        local_10 = -1;
      }
    }
    else {
      if ((size != -1) && (size < stripsize)) {
        stripsize = size;
      }
      iVar1 = TIFFFillStrip(tif,strip);
      if (iVar1 == 0) {
        local_10 = -1;
      }
      else {
        iVar1 = (*tif->tif_decodestrip)(tif,buf,stripsize,(uint16)(strip / uVar2));
        if (iVar1 < 1) {
          local_10 = -1;
        }
        else {
          (*tif->tif_postdecode)(tif,buf,stripsize);
          local_10 = stripsize;
        }
      }
    }
  }
  else {
    TIFFErrorExt(tif->tif_clientdata,"TIFFReadEncodedStrip","%lu: Strip out of range, max %lu",
                 (ulong)strip,(ulong)(tif->tif_dir).td_nstrips);
    local_10 = -1;
  }
  return local_10;
}