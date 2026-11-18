static int readContigStripsIntoBuffer(TIFF *in, unsigned char *buf) {
  unsigned char *buf_start = buf;
  unsigned char *buf_ptr = buf;
  uint32 bytes_read = 0;
  uint32 nstrips = TIFFNumberOfStrips(in);
  uint32 strip_size = TIFFStripSize(in);
  uint32 rows_read = 0;
  uint32 scanline_size;
  uint32 orientation;
  orientation = TIFFGetFieldDefaulted(in, 278, &orientation);
  scanline_size = TIFFScanlineSize(in);
  if (scanline_size == 0) {
    TIFFError("", "TIFF scanline size is zero!");
    return 0;
  }
  for (uint32 strip = 0; strip < nstrips; strip++) {
    bytes_read = TIFFReadEncodedStrip(in, strip, buf_ptr, (tmsize_t)-1);
    rows_read = bytes_read / scanline_size;
    if (strip < nstrips - 1 && bytes_read != strip_size) {
      TIFFError("", "Strip %d: read %lu bytes, strip size %lu", strip + 1,
                bytes_read, strip_size);
    }
    if (bytes_read < 0 && !ignore_read_errors) {
      TIFFError("", "Error reading strip %lu after %lu rows", strip, rows_read);
      return 0;
    }
    buf_ptr += bytes_read;
  }
  return 1;
}