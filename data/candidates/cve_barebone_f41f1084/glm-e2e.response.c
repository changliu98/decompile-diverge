int sdp_parse_fmtp_config_h264(AVCodecContext *ctx, PacketType *pt, const char *attr, const char *value) {
    int ret = 0;

    if (strcmp(attr, "packetization-mode") == 0) {
        av_log(ctx, 48, "packetization-mode: %d\n", atoi(value));
        pt->profile_level_id = atoi(value);
        if (pt->profile_level_id > 1) {
            av_log(ctx, 16, "Unsupported packetization-mode: %d\n", pt->profile_level_id);
        }
    } else if (strcmp(attr, "profile-level-id") == 0) {
        if (strlen(value) == 6) {
            parse_profile_level_id(ctx, pt, value);
        }
    } else if (strcmp(attr, "sprop-parameter-sets") == 0) {
        if (value[strlen(value) - 1] == ',') {
            av_log(ctx, 24, "Trailing comma in sprop-parameter-sets\n");
            ret = 0;
        } else {
            pt->extradata_size = 0;
            av_freep(&pt->extradata);
            ret = ff_h264_parse_sprop_parameter_sets(ctx, pt, &pt->extradata, value);
            av_log(ctx, 48, "Parsed extradata: %p, size: %d\n", pt->extradata, pt->extradata_size);
        }
    }

    return ret;
}