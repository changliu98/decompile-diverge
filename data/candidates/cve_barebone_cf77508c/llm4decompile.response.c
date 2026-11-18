int jpegxl_anim_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    JXLAnimDemuxContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t size = avio_size(pb);
    size_t offset = 0;
    int ret;

    if (size < 0)
        return size;

    if (!size)
        size = 4096;

    if (ctx->buf && ctx->buf->size > size)
        size = ctx->buf->size;

    ret = av_new_packet(pkt, size);
    if (ret < 0)
        return ret;

    if (ctx->buf) {
        offset = ctx->buf->size;
        memcpy(pkt->data, ctx->buf->data, offset);
        av_buffer_unref(&ctx->buf);
    }

    ret = avio_read(pb, pkt->data + offset, size - offset);
    if (ret < 0)
        return ret;

    if (ret < size - offset)
        pkt->size = offset + ret;

    return 0;
}