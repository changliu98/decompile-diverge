int skip_boxes(JXLParseContext *ctx, const uint8_t *buf, int buf_size)
{
    GetByteContext gb;

    if (buf_size < ctx->skip)
        return -1404930114;

    bytestream2_init(&gb, buf + ctx->skip, buf_size - ctx->skip);

    while (1) {
        uint32_t size;
        uint64_t size64;
        int head_size = 4;

        if (bytestream2_peek_le16(&gb) == 0xAFF)
            break;

        if (bytestream2_peek_le64(&gb) == 0x204C584A0C000000)
            break;

        if (bytestream2_get_bytes_left(&gb) < 8)
            return -1404930114;

        size = bytestream2_get_be32(&gb);
        if (size == 1) {
            if (bytestream2_get_bytes_left(&gb) < 12)
                return -1404930114;
            size64 = bytestream2_get_be64(&gb);
            head_size += 8;
            if (size64 > 0xFFFFFFFF)
                return -1404930114;
            size = (uint32_t)size64;
        }

        if (size == 0)
            return -1122319017;

        if (size <= head_size + 4)
            return -1122319017;

        ctx->skip += size;

        bytestream2_skip(&gb, size - head_size);

        if (bytestream2_get_bytes_left(&gb) <= 0)
            return -1404930114;
    }

    return 0;
}