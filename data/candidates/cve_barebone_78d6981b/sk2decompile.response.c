ssize_t cdf_read_short_sector(const cdf_header_t *h, void *buf, unsigned offset,
                              unsigned size, const cdf_super_t *s,
                              cdf_secid_t id) {
  unsigned pos = id * (1 << s->s_log2_ssize);
  if (1 << s->s_log2_ssize != size) {
    assert(1 << s->s_log2_ssize == size);
    return -1;
  }
  if (pos > h->h_size * (1 << s->s_log2_bsize)) return -1;
  memcpy((char *)buf + offset, h->h_data + pos, size);
  return size;
}