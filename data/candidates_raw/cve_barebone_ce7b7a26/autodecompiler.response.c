static int
dump_strip(TIFF* tif, char* buf)
{
 char* cp = buf;
 tsize_t cc = 0;
 uint32 nstrips, stripsize, rowsperstrip, rows;
 tsize_t scanline_size;
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
  if (strip >= nstrips)
   break;
  cc = TIFFReadEncodedStrip(tif, strip, cp, (tsize_t) -1);
  rows = (uint32)(cc / scanline_size);
  if (strip < nstrips-1 && cc != stripsize) {
   TIFFError("tiffdump",
       "Strip %d: read %lu bytes, strip size %lu",
       strip, (unsigned long) cc, (unsigned long) stripsize);
  }
  if (cc < 0 && !ignore) {
   TIFFError("tiffdump",
       "Error reading strip %lu after %lu rows",
       (unsigned long) strip, (unsigned long) rows);
   ok = 0;
   break;
  }
  cp += cc;
 }
 ok = 1;
 return (ok);
}