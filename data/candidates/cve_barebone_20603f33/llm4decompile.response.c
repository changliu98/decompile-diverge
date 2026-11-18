int
readContigStripsIntoBuffer(TIFF* tif, uint8* buf)
{
    uint32 nstrips = TIFFNumberOfStrips(tif);
    uint32 strip, rows = 0;
    tmsize_t stripsize = TIFFStripSize(tif);
    tmsize_t scanline_size;
    uint32 rowsperstrip = TIFFGetFieldDefaulted(tif, 278, &rowsperstrip);
    int32 bytes_read = 0;

    scanline_size = TIFFScanlineSize(tif);
    if (scanline_size == 0) {
        TIFFError("", "TIFF scanline size is zero!");
        return (0);
    }

    for (strip = 0; strip < nstrips; strip++) {
        bytes_read = TIFFReadEncodedStrip(tif, strip, buf, -1);
        rows += bytes_read / scanline_size;
        if (strip < nstrips - 1 && bytes_read != stripsize)
            TIFFError("", "Strip %d: read %lu bytes, strip size %lu",
                      strip + 1, (unsigned long) bytes_read,
                      (unsigned long) stripsize);
        if (bytes_read < 0 && !ignore) {
            TIFFError("", "Error reading strip %lu after %lu rows",
                      (unsigned long) strip, (unsigned long) rows);
            return (0);
        }
        buf += bytes_read;
    }
    return (1);
}