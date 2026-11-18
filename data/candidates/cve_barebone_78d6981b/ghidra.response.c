ssize_t cdf_read_short_sector
                  (cdf_stream_t *sst,void *buf,size_t offs,size_t len,cdf_header_t *h,cdf_secid_t id
                  )

{
  ulong uVar1;
  size_t pos;
  size_t ss;
  cdf_secid_t id_local;
  cdf_header_t *h_local;
  size_t len_local;
  size_t offs_local;
  void *buf_local;
  cdf_stream_t *sst_local;
  size_t local_10;
  
  uVar1 = (long)id * (long)(1 << ((byte)h->h_short_sec_size_p2 & 0x1f));
  if ((long)(1 << ((byte)h->h_short_sec_size_p2 & 0x1f)) == len) {
    if ((long)(1 << ((byte)h->h_sec_size_p2 & 0x1f)) * sst->sst_len < uVar1) {
      local_10 = 0xffffffffffffffff;
    }
    else {
      memcpy((void *)((long)buf + offs),(void *)((long)sst->sst_tab + uVar1),len);
      local_10 = len;
    }
    return local_10;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("ss == len","/work/harness.c",0x53,
                "ssize_t cdf_read_short_sector(const cdf_stream_t *, void *, size_t, size_t, const cdf_header_t *, cdf_secid_t)"
               );
}