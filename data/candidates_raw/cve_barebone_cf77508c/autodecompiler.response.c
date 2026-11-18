__attribute__((used)) static int read_audio(AVFormatContext *s, AVPacket *pkt)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t size;
    int ret;
    unsigned pos = 0;

    size = avio_size(pb);
    if (size < 0)
        return size;

    /* don't read more than the specified size */
    if (!size && asf->packet_size)
        size = asf->packet_size;

    /* if we know the file size, then we can calculate the last timestamp */
    if (asf->packet_size && asf->packet_size < (unsigned)size)
        size = asf->packet_size;

    ret = av_new_packet(pkt, size);
    if (ret < 0)
        return ret;

    /* if there is a pre-read packet, copy it to the beginning of the buffer */
    if (asf->pre_pkt) {
        pos = asf->pre_pkt->size;
        memcpy(pkt->data, asf->pre_pkt->data, pos);
        av_buffer_unref(&asf->pre_pkt);
    }

    ret = avio_read(pb, pkt->data + pos, size - pos);
    if (ret < 0)
        return ret;

    if (ret < size - pos)
        pkt->size = ret + pos;

    return 0;
}