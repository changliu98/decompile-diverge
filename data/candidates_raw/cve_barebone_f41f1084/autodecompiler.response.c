__attribute__((used)) static int h264_handle_packet(AVFormatContext *ctx,
                              PayloadContext *data, AVPacket *pkt,
                              const char *attr, const char *value)
{
    H264Context *h = data->priv_data;
    int ret;

    if (!strcmp(attr, "packetization-mode")) {
        AVCodecContext *avctx = &ctx->streams[0]->codec;
        av_log(ctx, AV_LOG_DEBUG, "RTP Packetization Mode: %d\n", atoi(value));
        /* we support modes 0 and 1 */
        h->packetization_mode = atoi(value);
        if (h->packetization_mode > 1)
            av_log(ctx, AV_LOG_WARNING, "Interleaved RTP mode is not supported yet.\n");
    } else if (!strcmp(attr, "profile-level-id")) {
        if (strlen(value) == 6)
            parse_profile_level_id(ctx, h, value);
    } else if (!strcmp(attr, "sprop-parameter-sets")) {
        char *end = strchr(value, ',');
        if (end == value[strlen(value) - 1]) {
            av_log(ctx, AV_LOG_WARNING, "Missing PPS in sprop-parameter-sets, ignoring\n");
            ret = 0;
        } else {
            h->extradata_size = 0;
            av_freep(&h->extradata);
            ret = ff_h264_parse_sprop_parameter_sets(ctx, h, &h->extradata_size,
                                                      value, end - value);
            av_log(ctx, AV_LOG_DEBUG, "Extradata set to %p (size: %d)\n",
                   h->extradata, h->extradata_size);
        }
    } else {
        return AVERROR_INVALIDDATA;
    }

    return ret;
}