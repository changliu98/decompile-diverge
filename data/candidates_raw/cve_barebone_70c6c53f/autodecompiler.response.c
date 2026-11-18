__attribute__((used)) static int speex_decode_frame_header(AVCodecContext *avctx,
                                      unsigned char *buf, int buf_size)
{
    SpeexContext *s = avctx->priv_data;
    char *header;
    int ret;

    /* check for "Speex   " */
    header = av_strnstr(buf, "Speex   ", buf_size);
    if (!header) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    header += 28;

    s->speex_version_id = bytestream_get_le32(&header);
    if (s->speex_version_id > 1) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    s->header_size      = bytestream_get_le32(&header);
    if (s->header_size < 0 || s->header_size > 3) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    s->frames_per_packet = bytestream_get_le32(&header);
    if (s->frames_per_packet != 4) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    s->mode            = bytestream_get_le32(&header);
    if (s->mode < 0 || s->mode > 2) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    s->frame_size = bytestream_get_le32(&header);
    if (s->frame_size < (160 << !!s->header_size)) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }
    s->frame_size *= 1 + !!s->header_size;

    s->vbr = bytestream_get_le32(&header);

    s->nb_channels = bytestream_get_le32(&header);
    if (s->nb_channels < 1 || s->nb_channels > 64 ||
        s->nb_channels > (7680 / s->frame_size)) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    s->bitrate = bytestream_get_le32(&header);
    if (s->bitrate <= 0 || s->bitrate > 1000000000 / s->mode / s->frame_size) {
        ret = -0x41455358; // 'SPEX'
        goto fail;
    }

    s->frames = bytestream_get_le32(&header);

    return 0;

fail:
    av_log(avctx, AV_LOG_ERROR, "Invalid SPEX header\n");
    return ret;
}