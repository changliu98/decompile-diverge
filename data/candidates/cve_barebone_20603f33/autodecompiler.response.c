static int
readContigStripsIntoBuffer(TIFF* tif, char* buf)
{
 char* cp = buf;
 tsize_t stripsize, scanline_size;
 uint32 rowsperstrip, rows;
 tsample_t s;
 tstrip_t nstrips, strip;
 int ok;

 nstrips = TIFFNumberOfStrips(tif);
 stripsize = TIFFStripSize(tif);
 rows = 0;
 rowsperstrip = TIFFGetFieldDefaulted(tif, 278, &rows);
 scanline_size = TIFFScanlineSize(tif);

 if (scanline_size == 0) {
  TIFFError("tiffdump",
      "TIFF scanline size is zero!");
  return (0);
 }

 for (strip = 0; ; strip++) {
  if (strip >= nstrips) {
   ok = 1;
   break;
  }
  bytes_read = TIFFReadEncodedStrip(tif, strip, cp, (tsize_t)-1);
  rows = bytes_read / scanline_size;
  if (strip < nstrips-1 && bytes_read != stripsize) {
   TIFFError("tiffdump",
       "Strip %d: read %lu bytes, strip size %lu",
       strip, (unsigned long) bytes_read,
       (unsigned long) stripsize);
  }
  if (bytes_read < 0 && !ignore) {
   TIFFError("tiffdump",
       "Error reading strip %lu after %lu rows",
       (unsigned long) strip, (unsigned long) rows);
   ok = 0;
   break;
  }
  cp += bytes_read;
 }
 return (ok);
}