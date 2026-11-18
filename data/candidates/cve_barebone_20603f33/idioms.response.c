int readContigStripsIntoBuffer(void *in, void *buf)
{
  struct tiff *tiff = (struct tiff *)in;
  struct tdata *tdata = (struct tdata *)buf;
  int ret = 0;
  unsigned int nstrips = get_nstrips(tiff);
  unsigned int stripsize = get_stripsize(tiff);
  unsigned int rows = 0;
  unsigned int rowpixels = get_rowpixels(tiff);
  unsigned int scanline_size = get_scanline_size(tiff);
  if (scanline_size == 0)
  {
    log_error("", "TIFF scanline size is zero!");
    return 0;
  }
  for (unsigned int i = 0; i < nstrips; i++)
  {
    ret = read_strip(tiff, i, tdata, -1);
    rows = ret / scanline_size;
    if (i < nstrips - 1 && ret != stripsize)
    {
      log_error("", "Strip %d: read %lu bytes, strip size %lu",
                i + 1, (unsigned long)ret, (unsigned long)stripsize);
    }
    if (ret < 0 && !ignore)
    {
      log_error("", "Error reading strip %lu after %lu rows",
                i, (unsigned long)rows);
      return 0;
    }
    tdata += ret;
  }
  return 1;
}