define AVERROR_INVALIDDATA 0xbebbb1b7

int parse_speex_extradata(struct SpeexContext *ctx, const char *extradata, int extradata_size) {
    int ret = AVERROR_INVALIDDATA;
    const uint8_t *buf = (const uint8_t *)extradata;
    const char *p = av_strnstr(extradata, "Speex   ", extradata_size);

    if (!p)
        return ret;

    buf = (const uint8_t *)(p + 28); // Skip "Speex   " (8 bytes) + 20 bytes offset

    ctx->field_0 = bytestream_get_le32(&buf);
    ctx->field_4 = bytestream_get_le32(&buf);
    if (ctx->field_4 <= 0)
        return ret;

    ctx->field_8 = bytestream_get_le32(&buf);
    if (ctx->field_8 < 0 || ctx->field_8 >= 3)
        return ret;

    ctx->field_c = bytestream_get_le32(&buf);
    if (ctx->field_c != 4)
        return ret;

    ctx->field_10 = bytestream_get_le32(&buf);
    if (ctx->field_10 <= 0 || ctx->field_10 > 2)
        return ret;

    ctx->field_14 = bytestream_get_le32(&buf);
    ctx->field_18 = bytestream_get_le32(&buf);

    int min_frame_size = 0xa0 << (ctx->field_8 > 0);
    if (ctx->field_18 < min_frame_size)
        return ret;

    ctx->field_18 *= (ctx->field_8 > 0) + 1;

    ctx->field_1c = bytestream_get_le32(&buf);
    ctx->field_20 = bytestream_get_le32(&buf);

    if (ctx->field_20 <= 0 || ctx->field_20 > 64)
        return ret;

    int max_val = 0x7fffffff / ctx->field_10 / ctx->field_18;
    if (ctx->field_20 >= max_val)
        return ret;

    ctx->field_24 = bytestream_get_le32(&buf);

    return 0;
}