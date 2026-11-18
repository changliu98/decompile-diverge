ssize_t __cdecl cdf_read_short_sector(
        const cdf_stream_t *sst,
        void *buf,
        size_t offs,
        size_t len,
        const cdf_header_t *h,
        cdf_secid_t id)
{
    size_t short_sec_size = 1 << h->h_short_sec_size_p2;
    size_t sec_size = 1 << h->h_sec_size_p2;
    size_t pos = short_sec_size * (size_t)id;

    // Original assertion: 1 << h->h_short_sec_size_p2 != len
    assert(len == short_sec_size && "ss == len");

    // Boundary check: Ensure the calculated offset doesn't exceed the stream's total size
    if (pos > sst->sst_len * sec_size)
        return -1LL;

    memcpy((char *)buf + offs, (char *)sst->sst_tab + pos, len);
    return len;
}