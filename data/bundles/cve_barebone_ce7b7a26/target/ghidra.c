int readContigStripsIntoBuffer(TIFF *in,uint8 *buf)

{
  tmsize_t tVar1;
  tmsize_t tVar2;
  tsize_t scanline_size;
  uint32 rps;
  uint32 rows;
  uint32 stripsize;
  uint32 nstrips;
  uint32 strip;
  int32 bytes_read;
  uint8 *bufp;
  uint8 *buf_local;
  TIFF *in_local;
  int local_c;
  
  bytes_read = 0;
  bufp = buf;
  buf_local = buf;
  in_local = in;
  nstrips = TIFFNumberOfStrips(in);
  tVar1 = TIFFStripSize(in_local);
  stripsize = (uint32)tVar1;
  rows = 0;
  rps = TIFFGetFieldDefaulted(in_local,0x116,&rps);
  tVar1 = TIFFScanlineSize(in_local);
  if (tVar1 == 0) {
    TIFFError("","TIFF scanline size is zero!");
    local_c = 0;
  }
  else {
    for (strip = 0; strip < nstrips; strip = strip + 1) {
      tVar2 = TIFFReadEncodedStrip(in_local,strip,bufp,-1);
      bytes_read = (int32)tVar2;
      rows = (uint32)((long)bytes_read / tVar1);
      if ((strip < nstrips - 1) && (bytes_read != stripsize)) {
        TIFFError("","Strip %d: read %lu bytes, strip size %lu",(ulong)(strip + 1),(long)bytes_read,
                  (ulong)stripsize);
      }
      if ((bytes_read < 0) && (ignore == 0)) {
        TIFFError("","Error reading strip %lu after %lu rows",(ulong)strip,(ulong)rows);
        return 0;
      }
      bufp = bufp + bytes_read;
    }
    local_c = 1;
  }
  return local_c;
}