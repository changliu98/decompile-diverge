int readContigStripsIntoBuffer(void* tif, void* buf) {
    void* current_buf = buf;
    int read_size = 0;
    int num_strips = TIFFNumberOfStrips(tif);
    int strip_size = TIFFStripSize(tif);
    int rows_per_strip = 0;
    long scanline_size = TIFFScanlineSize(tif);

    if (scanline_size == 0) {
        TIFFError("TIFFScanlineSize.module", "scanline size is zero");
        return 0;
    }

    for (int i = 0; i < num_strips; i++) {
        read_size = TIFFReadEncodedStrip(tif, i, current_buf, -1);
        int rows_in_strip = read_size / scanline_size;

        if (i < num_strips - 1 && read_size != strip_size) {
            TIFFError("TIFFScanlineSize.module", "strip %d size is %d, expected %d", i + 1, read_size, strip_size);
        }

        if (read_size < 0) {
            if (!ignore) {
                TIFFError("TIFFScanlineSize.module", "read error at strip %d, rows read %d", i, rows_in_strip);
            }
            return 0;
        }

        current_buf = (void*)((uintptr_t)current_buf + read_size);
    }

    return 1;
}