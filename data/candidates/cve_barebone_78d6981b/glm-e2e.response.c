size_t cdf_read_short_sector(
    const struct cdf_stream *sst,
    void *buf,
    size_t pos,
    size_t len,
    const struct cdf_header *h,
    int count
) {
    size_t ssat_sector_size = 1 << h->ssat_size_p2;
    size_t total_len = (size_t)count * ssat_sector_size;

    assert(len == ssat_sector_size);

    if (total_len > (1 << h->sec_size_p2) * sst->length) {
        return (size_t)-1;
    }

    memcpy(buf + pos, sst->buf + total_len, len);

    return len;
}