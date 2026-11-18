int parse_speex_extradata(AVCodecContext *avctx,
                                 const uint8_t *extradata, int extradata_size)
{
    SpeexContext *s = avctx->priv_data;
    const uint8_t *ptr = extradata;

    ptr = av_strnstr(ptr, "Speex   ", extradata_size);
    if (!ptr)
        return -0x41444E49;
    ptr += 7;

    s->version_id = bytestream_get_le32(&ptr);
    s->rate = bytestream_get_le32(&ptr);
    if (s->rate <= 0)
        return -0x41444E49;
    s->mode = bytestream_get_le32(&ptr);
    if (s->mode < 0 || s->mode > 2)
        return -0x41444E49;
    s->bitstream_version = bytestream_get_le32(&ptr);
    if (s->bitstream_version != 4)
        return -0x41444E49;
    s->nb_channels = bytestream_get_le32(&ptr);
    if (s->nb_channels < 1 || s->nb_channels > 2)
        return -0x41444E49;
    s->bitrate = bytestream_get_le32(&ptr);
    s->frame_size = bytestream_get_le32(&ptr);
    if (s->frame_size < 160 << (s->mode > 0))
        return -0x41444E49;
    s->frame_size *= 1 + (s->mode > 0);
    s->vbr = bytestream_get_le32(&ptr);
    s->frames_per_packet = bytestream_get_le32(&ptr);
    if (s->frames_per_packet < 1 || s->frames_per_packet > 64 ||
        s->frames_per_packet >= 0x7FFFFFFF / s->nb_channels / s->frame_size)
        return -0x41444E49;
    s->extra_headers = bytestream_get_le32(&ptr);

    return 0;
}