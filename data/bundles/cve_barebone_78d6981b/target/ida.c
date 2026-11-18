ssize_t __cdecl cdf_read_short_sector(
        const cdf_stream_t *sst,
        void *buf,
        size_t offs,
        size_t len,
        const cdf_header_t *h,
        cdf_secid_t id)
{
  size_t pos; // [rsp+8h] [rbp-48h]

  pos = (1 << h->h_short_sec_size_p2) * (__int64)id;
  if ( 1 << h->h_short_sec_size_p2 != len )
    __assert_fail(
      "ss == len",
      "/work/harness.c",
      0x53u,
      "ssize_t cdf_read_short_sector(const cdf_stream_t *, void *, size_t, size_t, const cdf_header_t *, cdf_secid_t)");
  if ( pos > sst->sst_len * (1 << h->h_sec_size_p2) )
    return -1LL;
  memcpy((char *)buf + offs, (char *)sst->sst_tab + pos, len);
  return len;
}