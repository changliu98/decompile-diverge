static size_t atomic_fetch_add(buffer_t *b, size_t n)
{
    size_t ret = b->pos;
    b->pos += n;
    return ret;
}