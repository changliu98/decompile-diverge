int __cdecl readContigStripsIntoBuffer(TIFF *in, uint8 *buf)
{
  tmsize_t scanline_size; // [rsp+0h] [rbp-40h]
  uint32 rps; // [rsp+8h] [rbp-38h] BYREF
  uint32 rows; // [rsp+Ch] [rbp-34h]
  uint32 stripsize; // [rsp+10h] [rbp-30h]
  uint32 nstrips; // [rsp+14h] [rbp-2Ch]
  uint32 strip; // [rsp+18h] [rbp-28h]
  int32 bytes_read; // [rsp+1Ch] [rbp-24h]
  uint8 *bufp; // [rsp+20h] [rbp-20h]
  uint8 *bufa; // [rsp+28h] [rbp-18h]
  TIFF *ina; // [rsp+30h] [rbp-10h]

  ina = in;
  bufa = buf;
  bufp = buf;
  bytes_read = 0;
  nstrips = TIFFNumberOfStrips(in);
  stripsize = TIFFStripSize(in);
  rows = 0;
  rps = TIFFGetFieldDefaulted(in, 0x116u, &rps);
  scanline_size = TIFFScanlineSize(ina);
  if ( scanline_size )
  {
    for ( strip = 0; strip < nstrips; ++strip )
    {
      bytes_read = TIFFReadEncodedStrip(ina, strip, bufp, -1LL);
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
  else
  {
    TIFFError("", "TIFF scanline size is zero!");
    return 0;
  }
}