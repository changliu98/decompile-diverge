static int speex_decode_init(struct AVCodecContext *avctx, unsigned char *extradata, int extradata_size)
{
    struct SpeexContext *ctx = avctx->priv_data;
    unsigned char *p = extradata;
    if (!check_string(p, "Speex   ", extradata_size))
        return -1094995529;
    p += 28;
    ctx->version_id = get_le32(&p);
    p += 4;
    ctx->rate = get_le32(&p);
    if (ctx->rate <= 0)
        return -1094995529;
    ctx->mode = get_le32(&p);
    if (ctx->mode >= 3)
        return -1094995529;
    ctx->bitstream_version = get_le32(&p);
    if (ctx->bitstream_version != 4)
        return -1094995529;
    ctx->nb_channels = get_le32(&p);
    if (ctx->nb_channels <= 0 || ctx->nb_channels > 2)
        return -1094995529;
    ctx->bitrate = get_le32(&p);
    ctx->frame_size = get_le32(&p);
    if (ctx->frame_size < (160 * (ctx->mode > 0)))
        return -1094995529;
    ctx->frame_size += (ctx->mode > 0);
    ctx->vbr = get_le32(&p);
    ctx->frames_per_packet = get_le32(&p);
    if (ctx->frames_per_packet <= 0
        || ctx->frames_per_packet > 64
        || ctx->frames_per_packet >= (0x7fffffff / ctx->nb_channels / ctx->frame_size))
        return -1094995529;
    ctx->extra_headers = get_le32(&p);
    return 0;
}