int64_t TIFFReadEncodedStrip(struct Tiff* tif, uint32_t strip, void* buf, int64_t size) {
    struct TiffDirectory* td = &tif->tif_dir;
    int64_t ret_val = -1;

    if (!TIFFCheckRead(tif, 0)) {
        return -1;
    }

    if (strip >= td->td_nstrips) {
        TIFFErrorExt(tif->client, TIFFReadEncodedStrip.module, "%u: strip out of range, max %u", strip, td->td_nstrips);
        return -1;
    }

    uint32_t rowsperstrip = td->td_rowsperstrip;
    if (rowsperstrip > td->td_imagelength) {
        rowsperstrip = td->td_imagelength;
    }

    uint32_t stripsperimage = (td->td_imagelength + rowsperstrip - 1) / rowsperstrip;
    uint32_t strip_in_group = strip % stripsperimage;
    uint16_t plane = strip / stripsperimage;
    
    uint32_t nstrips = td->td_imagelength - (strip_in_group * rowsperstrip);
    if (nstrips > rowsperstrip) {
        nstrips = rowsperstrip;
    }

    uint64_t stripsize = TIFFVStripSize(tif, nstrips);
    if (stripsize == 0) {
        return -1;
    }

    // Check if compression is 1 (no compression) and size is valid
    if (td->td_compression == 1 && size != -1 && size >= (int64_t)stripsize) {
        // Check flags: 0x800 (TIFF_BUFFERMMAP) and 0x20000 (TIFF_NOREADRAW)
        if ((tif->tif_flags & 0x800) == 0 && (tif->tif_flags & 0x20000) == 0) {
            if (TIFFReadRawStrip1(tif, strip, buf, stripsize, TIFFReadEncodedStrip.module) != (int64_t)stripsize) {
                return -1;
            }

            // Check flags: td_fillorder and 0x100 (TIFF_MAPPED)
            if ((tif->tif_flags & td->td_fillorder) == 0 && (tif->tif_flags & 0x100) == 0) {
                TIFFReverseBits(buf, stripsize);
            }

            tif->tif_postdecode(tif, buf, stripsize);
            return stripsize;
        }
    }

    if (size != -1 && size < (int64_t)stripsize) {
        stripsize = size;
    }

    if (!TIFFFillStrip(tif, strip)) {
        return -1;
    }

    if (tif->tif_decodestrip(tif, buf, stripsize, plane) <= 0) {
        return -1;
    }

    tif->tif_postdecode(tif, buf, stripsize);
    return stripsize;
}