ssize_t
cdf_read_short_sector(const cdf_stream_t *sst, char *buf, size_t offset,
 size_t len, const cdf_header_t *h, int sector)
{
 size_t ss = (size_t)1 << h->h_min_size_standard_stream;
 size_t off = (size_t)sector * ((size_t)1 << h->h_min_size_standard_stream);
 ssize_t ret;

 do { if (!(ss == len)) ___assert_fail("ss == len", "harness.c", 83, "ssize_t cdf_read_short_sector(const cdf_stream_t *, void *, size_t offset, size_t len, const cdf_header_t *h, int sector)"); } while (0);







 if (off > sst->sst_size * ((size_t)1 << h->h_min_size_short_stream))
  ret = -1;
 else {
  memcpy(buf + offset, sst->sst_tab + off, len);
  ret = len;
 }
 return ret;
}