int readContigStripsIntoBuffer(TIFF *tif, unsigned char *buf) {
    unsigned char *p = buf;
    int32_t read_size = 0;
    uint32_t nstrips = TIFFNumberOfStrips(tif);
    tmsize_t stripsize = TIFFStripSize(tif);
    int32_t scanlines = 0;
    uint16_t compression;
    TIFFGetFieldDefaulted(tif, 278, &compression); // 278 is 0x116 (TIFFTAG_ROWSPERSTRIP)
    tmsize_t scanline_size = TIFFScanlineSize(tif);
    
    if (scanline_size == 0) {
        TIFFError("", "Width * Depth != 0 or scanline size is zero");
        return 0;
    }

    for (uint32_t s = 0; s < nstrips; s++) {
        read_size = TIFFReadEncodedStrip(tif, s, p, -1);
        scanlines = read_size / scanline_size;
        
        if (s < nstrips - 1 && read_size != stripsize) {
            TIFFError("", "Strip %d: read %lu bytes, strip size %lu", s + 1, read_size, stripsize);
        }
        
        if (read_size < 0 && ignore == 0) {
            TIFFError("", "Strip %d: read error, scanlines %d", s, scanlines);
            return 0;
        }
        
        p += read_size;
    }
    
    return 1;
}