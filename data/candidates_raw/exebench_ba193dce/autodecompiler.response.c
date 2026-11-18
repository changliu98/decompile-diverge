int
_TIFFNoPostDecode(TIFF* tif, uint8* buf, tmsize_t cc)
{
    (void) tif; (void) buf; (void) cc;
    *buf = 1;
    *cc = 0;
    return 0;
}