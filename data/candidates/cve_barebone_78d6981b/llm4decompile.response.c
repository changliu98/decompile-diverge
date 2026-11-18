ssize_t
cdf_read_short_sector(const cdf_stream_t *sst, void *buf, size_t offs,
    size_t len, const cdf_header_t *h, cdf_secid_t id)
{
 size_t ss = (size_t)(1 << h->h_short_sec_size_p2);
 size_t pos = (size_t)id * ss;

 (void)(((ss == len) || __assert_fail("ss == len", "/work/harness.c", 83, "ssize_t cdf_read_short_sector(const cdf_stream_t *, void *, size_t, size_t, const cdf_header_t *, cdf_secid_t)")))
                                                                   ;

 if (pos > sst->sst_len * (size_t)(1 << h->h_sec_size_p2))
  return -1;

 memcpy((char *)buf + offs, sst->sst_tab + pos, len);
 return (ssize_t)len;
}