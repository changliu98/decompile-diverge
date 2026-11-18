static int jxl_read_packet(struct AVFormatContext *ctx, struct AVPacket *pkt)
{
    struct JXLAnimDemuxContext *c = ctx->priv_data;
    struct AVIOContext *pb = ctx->pb;
    long size;
    int ret;
    long offset = 0;
    size = avio_rl32(pb);
    if (size < 0)
        return size;
    if (size == 0)
        size = 4096;
    if (c->initial && c->initial->size < size)
        size = c->initial->size;
    ret = av_new_packet(pkt, size);
    if (ret < 0)
        return ret;
    if (c->initial) {
        offset = c->initial->size;
        av_strlcpy(pkt->data, c->initial->data, offset);
        av_free(c->initial);
    }
    ret = avio_read(pb, &pkt->data[offset], size - offset);
    if (ret < 0)
        return ret;
    if (ret < size - offset)
        pkt->size = offset + ret;
    return 0;
}