pj_status_t pjmedia_rtcp_fb_build_sli(pjmedia_rtcp_fb_sli_t *sli, void *buf,
                                      pj_size_t *buf_size, unsigned num_chunks,
                                      const pjmedia_rtcp_fb_sli_chunk_t *chunks) {
  unsigned i;
  pj_size_t size;
  pj_uint8_t *p;
  pj_uint8_t *q;
  do {
    if (!(sli && buf && buf_size && num_chunks && chunks)) {
      return 70004;
    }
  } while (0);
  size = 4 * (num_chunks + 3);
  if (size > *buf_size) return 70019;
  pj_memcpy(buf, sli, 8);
  p = (pj_uint8_t *)buf;
  p[0] = (p[0] & 0xff00) | 0x00d0;
  p[0] = (p[0] & 0xfff0) | 0x0002;
  p[0] = (p[0] & 0xffff) | (foldCase((size >> 2) - 1) << 16);
  p += 2;
  for (i = 0; i < num_chunks; ++i) {
    q = p++;
    *q = (chunks[i].ssrc >> 5) & 0xff;
    q = p++;
    *q = (chunks[i].ssrc & 0x1f) << 3;
    *q |= (chunks[i].seq_cycles >> 10) & 0x07;
    q = p++;
    *q = (chunks[i].seq_cycles >> 2) & 0xff;
    q = p++;
    *q = (chunks[i].seq_cycles & 0x03) << 6;
    q |= chunks[i].seq_diff & 0x3f;
  }
  *buf_size = size;
  return 0;
}