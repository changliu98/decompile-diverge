static long cdf_read_short_sector(const cdf_stream_t *sst, void *buf, unsigned long offs, unsigned long len, const cdf_header_t *h, cdf_secid_t id)
{
  unsigned long off = h->h_sec_size_p2 * id;
  do { if (!(1 == len)) { cdf_assert("ss == len", "/work/harness.c", 83, __PRETTY_FUNCTION__); } } while (0);
  if (off > sst->sst_len * h->h_sec_size_p2)
    return -1;
  cdf_copy(buf + offs, sst->sst_tab + off, len);
  return len;
}