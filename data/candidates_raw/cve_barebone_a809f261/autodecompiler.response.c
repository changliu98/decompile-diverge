__attribute__((used)) static int check_file_header(AVFormatContext *s, uint8_t *buffer, int buf_size)
{
    GetByteContext gbc;
    int ret;

    if (s->pb.size > 0 && s->pb.size <= buf_size) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    buffer += s->pb.size;
    buf_size -= s->pb.size;
    bytestream2_init(&gbc, buffer, buf_size);

    for (;;) {
        unsigned int next;
        int head_size;

        if (bytestream2_peek_le16(&gbc) == 0xaff) {
            ret = 0;
            break;
        } else if (bytestream2_peek_le64(&gbc) == 0x204c584a0c000000LL) {
            ret = 0;
            break;
        } else if (bytestream2_get_bytes_left(&gbc) < 9) {
            ret = AVERROR_INVALIDDATA;
            break;
        }

        next = bytestream2_get_be32(&gbc);
        head_size = 4;

        if (next == 1) {
            if (bytestream2_get_bytes_left(&gbc) < 9) {
                ret = AVERROR_INVALIDDATA;
                break;
            }
            next = bytestream2_get_be64(&gbc);
            head_size = 12;
        }

        if (!next) {
            ret = AVERROR_INVALIDDATA;
            break;
        }

        if (next <= head_size + 4) {
            ret = AVERROR_INVALIDDATA;
            break;
        }

        s->pb.size += next;
        bytestream2_skip(&gbc, next - head_size);

        if (bytestream2_get_bytes_left(&gbc) < 1) {
            ret = AVERROR_INVALIDDATA;
            break;
        }
    }

fail:
    return ret;
}