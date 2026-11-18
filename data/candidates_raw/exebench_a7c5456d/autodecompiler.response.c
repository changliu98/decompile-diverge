static size_t _buffer_advance(buffer_t *b, size_t n)
{
    size_t ret = b->pos;
    b->pos += n;
    return ret;
}