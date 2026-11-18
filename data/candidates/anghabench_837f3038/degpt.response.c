uint memcached_udp_set_cookie(uchar *buffer, size_t buffer_length, uint64_t sequence_number)
{
    if (1 < buffer_length) {
        *buffer = (uchar)(sequence_number >> 8);
        buffer[1] = (uchar)sequence_number;
    }
    return 0;
}