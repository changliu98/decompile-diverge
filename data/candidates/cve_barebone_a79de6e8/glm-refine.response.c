void __cdecl mobi_buffer_move(MOBIBuffer *buf, const int offset, const size_t len)
{
    size_t aoffset = abs(offset);
    unsigned __int8 *source = &buf->data[buf->offset];
    unsigned __int8 *target;

    if (offset < 0)
    {
        if (buf->offset < aoffset)
        {
            buf->error = MOBI_BUFFER_END;
            return;
        }
        target = source - aoffset;
    }
    else
    {
        if (len + aoffset + buf->offset > buf->maxlen)
        {
            buf->error = MOBI_BUFFER_END;
            return;
        }
        target = source + aoffset;
    }

    memmove(source, target, len);
    buf->offset += len;
}