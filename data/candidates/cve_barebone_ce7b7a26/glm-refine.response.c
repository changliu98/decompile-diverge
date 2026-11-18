int __cdecl readContigStripsIntoBuffer(TIFF *in, uint8 *buf)
{
  uint32 rps;             // [rbp-38h] BYREF
  uint32 rows;            // [rbp-34h]
  uint32 stripsize;       // [rbp-30h]
  uint32 nstrips;         // [rbp-2Ch]
  uint32 strip;           // [rbp-28h]
  int32 bytes_read;       // [rbp-24h]
  uint8 *bufp;            // [rbp-20h]
  tmsize_t scanline_size; // [rbp-40h]

  bufp = buf;
  nstrips = TIFFNumberOfStrips(in);
  stripsize = TIFFStripSize(in);
  rows = 0;
  
  // TIFFGetFieldDefaulted fills 'rps' with the value of tag 0x116 (TIFFTAG_ROWSPERSTRIP)
  rps = TIFFGetFieldDefaulted(in, 0x116u, &rps);
  
  scanline_size = TIFFScanlineSize(in);
  if ( scanline_size == 0 )
  {
    TIFFError("", "TIFF scanline size is zero!");
    return 0;
  }

  for ( strip = 0; strip < nstrips; ++strip )
  {
    bytes_read = TIFFReadEncodedStrip(in, strip, bufp, -1LL);
    rows = bytes_read / scanline_size;
    
    if ( strip < nstrips - 1 && bytes_read != stripsize )
      TIFFError("", "Strip %d: read %lu bytes, strip size %lu", strip + 1, bytes_read, stripsize);
      
    if ( bytes_read < 0 && !ignore )
    {
      TIFFError("", "Error reading strip %lu after %lu rows", strip, rows);
      return 0;
    }
    bufp += bytes_read;
  }
  
  return 1;
}