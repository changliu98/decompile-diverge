rstatus_t
memcached_udp_set_cookie(char *buf, const size_t size, uint64_t seqno)
{
    if (size >= 2) {
        char *px = (char *)buf;
        px[0] = (char)(seqno >> 8);
        px[1] = (char)(seqno & 0xff);
    }

    return 0;
}