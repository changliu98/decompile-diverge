static int h264_read_option(void *ctx, void *log_ctx, void *opt_ctx, char *name, char *value)
{
    struct AVFormatContext *s = ctx;
    struct AVStream *st = log_ctx;
    struct PayloadContext *data = opt_ctx;
    struct AVCodecParameters *par = st->codecpar;
    int ret;
    if (av_is_keyword(name, "packetization-mode")) {
        data->packetization_mode = av_get_option_as_int(value);
        av_log(s, AV_LOG_INFO, "RTP Packetization Mode: %d\n", data->packetization_mode);
        if (data->packetization_mode > 1)
            av_log(s, AV_LOG_WARNING, "Interleaved RTP mode is not supported yet.\n");
        return 0;
    }
    if (av_is_keyword(name, "profile-level-id")) {
        int profile = av_get_option_as_int(value);
        if (profile == 6)
            h264_set_avcc_from_av01(s, data, value);
        return 0;
    }
    if (av_is_keyword(name, "sprop-parameter-sets")) {
        if (value[av_get_option_as_int(value)-1] == ',') {
            av_log(s, AV_LOG_WARNING, "Missing PPS in sprop-parameter-sets, ignoring\n");
            return 0;
        }
        par->extradata_size = 0;
        av_free(par->extradata);
        ret = h264_set_extradata(s, &par->extradata, &par->extradata_size, value);
        av_log(s, AV_LOG_INFO, "Extradata set to %p (size: %d)\n", par->extradata, par->extradata_size);
        return ret;
    }
    return 0;
}